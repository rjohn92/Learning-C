# binkit

*A tiny, readable toolkit I’m building to get hands‑on with bytes, files, and C. First stop: a hexdump I can actually understand. You can follow along and extend it too.*

---

## Why this exists (and why hex matters)

I built **binkit** as my capstone for learning C fundamentals in a way that’s practical for systems/RE/CNO work. Hex isn’t some elite wizardry; it’s the most compact, readable way to see **raw bytes**:

* **Everything is bytes.** Text, images, executables, packets—under the hood it’s 0..255 values.
* **Hex = base‑16 view** of those bytes. Two hex digits (00–FF) represent one byte. It’s compact and lines up nicely with bits/bitmasks.
* **Why you’ll care:** verifying file headers (e.g., PNG starts `89 50 4E 47 …`), spotting Windows vs. Unix line endings (`0D 0A` vs `0A`), confirming buffers, locating offsets for patches, understanding encodings (UTF‑8 multibyte sequences), and generally thinking like a reverser.

This project keeps code small so you (and I) can understand every line, test it quickly, and grow it feature by feature.

---

## What this does (hexdump v0)

`hexdump` prints your input as rows of **16 bytes**. Each row begins with an **offset**—the byte index from the start—printed in 8 hex digits. Then each byte in that row prints as two hex digits.

Example (for `"hello\n"`):

```
00000000: 68 65 6C 6C 6F 0A
```

* `00000000:` → we’re at **offset 0** (start of stream). Next row would be `00000010:` (16 decimal = 0x10).
* `68 65 6C 6C 6F 0A` → bytes for `h e l l o \n`.

---

## How to run it (three styles)

Build a single‑file toy with a tiny `main`:

```c
// hexdump.c
#include <stdio.h>
int cmd_hexdump(int, char**);
int main(int argc, char **argv) { return cmd_hexdump(argc, argv); }
```

Compile:

```bash
gcc -Wall -Wextra -O0 -g hexdump.c -o hexdump
```

Run it any of these ways:

```bash
# 1) Filename argument → program opens the file
./hexdump hello.bin

# 2) Stdin redirection → shell feeds file bytes to stdin
./hexdump < hello.bin

# 3) Pipeline → previous program’s stdout becomes our stdin
printf 'hello\n' | ./hexdump
```

> All three produce the same output. The shell either passes you a **filename** via `argv` or a **byte stream** via `stdin`.

---

## Walkthrough of `hexdump.c` (syntax and reasoning)

Below is the minimal version I started with. I’ll annotate what each piece means and why it’s written that way.

```c
#include <stdio.h>

int cmd_hexdump(int argc, char **argv) {
    FILE *fp = stdin;                // default: read from standard input
    unsigned long offset = 0;        // how many bytes we’ve printed so far
    unsigned char byte;              // one byte buffer

    // If a filename is provided (and not an option), open it.
    if (argc > 1 && argv[1][0] != '-') {
        fp = fopen(argv[1], "rb");  // "rb" = binary mode (exact bytes on Windows)
        if (!fp) { perror("fopen"); return 1; }
    }

    // Read 1 byte at a time and print it in hex, 16 per line.
    while (fread(&byte, 1, 1, fp) == 1) {
        if (offset % 16 == 0) {
            // Print the starting offset for this row (8 hex digits)
            printf("%08lX: ", offset);
        }

        // Print the current byte as two hex digits
        printf("%02X ", byte);

        // Move to the next byte; if we've printed 16, end the line.
        offset++;
        if (offset % 16 == 0) {
            putchar('\n');
        }
    }

    // If we ended mid-row, print a final newline
    if (offset % 16 != 0) {
        putchar('\n');
    }

    if (fp != stdin) fclose(fp);
    return 0;
}
```

### `#include <stdio.h>`

* Pulls in declarations for `FILE`, `fopen`, `fread`, `fclose`, `printf`, `perror`, `putchar`.
* The **preprocessor** literally pastes the header text before compilation; linking to the stdio library happens later.

### `int cmd_hexdump(int argc, char **argv)`

* Conventional parameter names: not keywords. The types matter.
* `argc` = **count** of arguments (including `argv[0]`, the program name).
* `argv` = array of **C strings** (null‑terminated). `argv[argc] == NULL`.
* Mental model:

  ```
  argv[0] → "./hexdump"\0
  argv[1] → "hello.bin"\0
  argv[2] → NULL
  ```

### `FILE *fp = stdin;`

* `FILE` is a library struct (buffering, file descriptor, error flags). You hold a **pointer** to it (`FILE *`).
* `stdin` is a preopened `FILE *`. By default it’s your **terminal**; with `< file` or a pipe, the shell re‑wires it to come from a file or another process.

### `unsigned long offset = 0;`

* Tracks the **byte index** we’ve printed so far (0 at start). That’s all “offset” means.
* `unsigned` because offsets aren’t negative. `long` because files can be huge (often 64‑bit on Linux).
* Printed with `%08lX`: zero‑padded width **8**, **long**, **hex** uppercase.

### `unsigned char byte;`

* A raw byte is **0..255**. `unsigned char` guarantees that range. Some platforms have signed `char` (−128..127) which would corrupt values ≥ 128.

### The filename/option check

```c
if (argc > 1 && argv[1][0] != '-') { ... }
```

* If the first extra token doesn’t start with `-`, treat it as a **filename** and open it.
* Otherwise, keep using `stdin`. (This also means a lone `-` will keep stdin—common Unix shorthand.)

### The read/print loop

```c
while (fread(&byte, 1, 1, fp) == 1) {
    if (offset % 16 == 0) printf("%08lX: ", offset);
    printf("%02X ", byte);
    if (++offset % 16 == 0) putchar('\n');
}
```

* `fread(&byte, 1, 1, fp)` → attempt to read **one** item of **size 1**. Return `1` means success (we got a byte). Return `0` means **EOF or error**; check with `feof/ferror` if you care.
* `offset % 16 == 0` → we’re at the **start of a row**; print the address label.
* `%02X` → two hex digits per byte, zero‑padded (always `0A`, not `A`).
* After 16 bytes, print a newline.

### Final newline fix‑up

* If the last row had fewer than 16 bytes, we end the loop **mid‑row** and add one newline so the output is clean.

### Cleanup

* Only `fclose` if we opened a file. `stdin` is managed by the runtime.

---

## Char → hex: how conversion works (two mental models)

* **Divide‑by‑16 method:** take a byte value, divide by 16 → **quotient** = high digit, **remainder** = low digit. Map 10..15 to A..F. Example: `104 ÷ 16 = 6 r8` → `0x68` (that’s `'h'`).
* **Nibble method:** a byte is two 4‑bit halves. `hi = (b >> 4) & 0xF`, `lo = b & 0xF`; map each 0..15 to 0..9/A..F.
* `printf("%02X", b)` does that mapping for you. The `02` keeps columns aligned.

Try:

```bash
printf 'hello\n' | ./hexdump       # 68 65 6C 6C 6F 0A
printf '\n'        | ./hexdump       # 5C 6E (literal backslash + n)
python3 - <<'PY' | ./hexdump         # 20 bytes 1..20
import sys; sys.stdout.buffer.write(bytes(range(1,21)))
PY
```

---

## Debugging & best practices

* **Compile with warnings + debug symbols**: `-Wall -Wextra -O0 -g`
* **Use a known-good tool for comparison**: `xxd -g 1` (group by 1 byte). Your output should match the hex values.
* **Check EOF vs error** after reading:

  ```c
  if (ferror(fp)) { perror("read"); return 1; }
  ```
* **Test both input paths**: filename arg, redirection, and pipeline.
* **Watch line endings**: Unix newline = `0A`; Windows CRLF = `0D 0A`.
* **Keep stdin open**: only `fclose` what you `fopen`.

---

## Troubleshooting notes (things I hit, and fixes)

* **Why did my dump show** `70 72 69 6E 74 66 20 ...`?
  I accidentally *typed* a shell command into the running program. The program dutifully dumped the characters I typed. Fix: run the pipeline at the **shell prompt**, not inside the program; e.g., `printf 'hello\n' | ./hexdump`.
* **`\n` vs newline confusion**: `5C 6E` is the literal backslash‑n; a real newline is `0A`. Use `printf '...\n'` (with quotes), not `echo` unless you know your shell’s `-e` behavior.
* **Windows text mode**: use `"rb"` with `fopen` or you’ll get translated bytes.

---

## Where this can grow (and why)

To cover more of the C topics I practiced (and to make the tool actually handy), I plan to add:

* **Block reads (buffers)**: read 16 or 4096 bytes at a time, then format into 16‑byte rows. Same output, fewer calls → faster.
* **ASCII gutter**: show printable ASCII on the right; teaches `ctype.h` and padding logic.
* **Options parsing**: `-w <N>` (bytes/row), `-n <count>` (limit), `-s <offset>` (seek). Good practice for `argc/argv`, `strtoul`, and error paths.
* **Structs & pointers**: a small `struct Row { unsigned long off; unsigned char buf[16]; size_t n; };` to shuttle data into a formatter; pointer arithmetic to slice buffers.
* **Utilities module**: `util.{c,h}` with safe wrappers (e.g., `xfopen`, `xread`) and common parsing helpers.
* **Other commands**: `strings` (print printable runs), `slice` (copy a byte range), `xor` (stream XOR), `find` (hex pattern search), `sum` (checksums). Each teaches different fundamentals (loops, state machines, bitwise ops).

---

## FAQ (quick hits)

**Do I need to pass a filename?** No. You can pass a filename *or* pipe bytes in via stdin. Both work:

```
./hexdump file.bin
./hexdump < file.bin
cat file.bin | ./hexdump
```

**Why `unsigned char`?** Raw bytes are 0..255. A plain `char` can be signed on some systems and will corrupt values ≥ 128.

**Why 16 bytes per row?** It’s a convention that balances width and readability. You can change it later with `-w`.

**Why does the offset column look like `00000010`?** That’s hex with zero padding to width 8. `0x10` is 16 decimal—the start of the second row.

---
