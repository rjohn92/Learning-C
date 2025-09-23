# Module 11 — **GDB, Ghidra, and Valgrind** Deep Dive (Addendum)

> This addendum plugs straight into the main Module 11 lecture. It gives you a **practical, step‑by‑step** workflow for source‑level debugging (GDB + VS Code), reverse engineering (Ghidra), and runtime bug hunting (Valgrind & Sanitizers), with runnable demos, exact commands, what to expect, and *why* it works under the hood.

---

## 0) Quick Mental Model

* **C execution**: CPU runs *machine instructions*. Your `.c` file does not run; the compiled **ELF** does.
* **GDB** is a **process debugger**. It controls a running process via the OS (`ptrace`), sets breakpoints (trap instructions), single‑steps, and reads/writes memory and registers.
* **Source‑level stepping** is possible because the compiler emits **DWARF** debug info (`-g`) that maps instruction addresses ⇄ source lines and describes types/locals.
* **Ghidra** analyzes a binary to recover control flow, functions, and a C‑like decompilation.
* **Valgrind/Sanitizers** instrument the program at runtime to catch invalid memory use and undefined behavior.

---

## 1) Environment Setup & Best Practices

### 1.1 Install toolchain (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential gdb valgrind
```

*(Clang works too: `sudo apt install clang`)*

### 1.2 Always compile learning builds with debug‑friendly flags

```
-g -O0 -fno-omit-frame-pointer -Wall -Wextra -Wshadow -Wvla -Wconversion
```

Optional hardening: `-fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now`

### 1.3 VS Code integration (optional but recommended)

Create `.vscode/launch.json` (GDB launch):

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "(gdb) Launch app",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/app",
      "args": [],
      "cwd": "${workspaceFolder}",
      "stopAtEntry": false,
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",
      "setupCommands": [
        {"text": "-enable-pretty-printing"},
        {"text": "set disassembly-flavor intel"},
        {"text": "set print pretty on"}
      ],
      "showDisassembly": "never",
      "disassemblyFlavor": "intel",
      "skipFiles": ["<builtin>", "**/lib/**", "**/libc/**"]
    }
  ]
}
```

Build task `.vscode/tasks.json`:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build app",
      "type": "shell",
      "command": "gcc -g -O0 -fno-omit-frame-pointer -Wall -Wextra main.c -o app",
      "group": "build",
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

**Why these flags?** `-g` exposes line tables/types to GDB/Ghidra; `-O0` prevents aggressive reordering/inlining; `-fno-omit-frame-pointer` keeps clean backtraces.

---

## 2) GDB: What, Why, and Exactly How

### 2.1 What GDB is / Why it works

* Controls your process via **ptrace**: insert breakpoint traps, single‑step, read/write registers and memory.
* Uses **DWARF** metadata to map **addresses** back to **source lines, locals, and types**.
* Result: you *see* and step C lines, but the CPU is executing instructions.

### 2.2 Minimal “Pointer Anatomy” Demo (hands‑on)

**`main.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct S { int a; int b; };

static void fill(char *dst, size_t n, char c){ memset(dst, c, n); }

int main(int argc, char **argv){
    char buf[32] = {0};              // stack buffer
    struct S s = { .a = 10, .b = 20 }; // stack struct
    struct S *p = &s;                 // pointer to struct

    fill(buf, sizeof buf - 1, 'A');   // write 'A' bytes
    printf("buf=%s\n", buf);

    printf("&s=%p &p=%p p=%p\n", (void*)&s, (void*)&p, (void*)p);
    printf("s.a=%d s.b=%d; via p: a=%d b=%d\n", s.a, s.b, p->a, p->b);

    char *heap = malloc(16);
    strcpy(heap, argc>1? argv[1] : "hi");
    printf("heap=%p heap[0]=%d\\n", (void*)heap, heap[0]);
    free(heap);
    return 0;
}
```

**Build & run under GDB**

```bash
gcc -g -O0 -fno-omit-frame-pointer main.c -o app
gdb ./app
(gdb) break main
(gdb) run
```

**Step & inspect (what to do / what to see)**

```gdb
(gdb) next                    # step to buf declaration
(gdb) info locals             # see uninitialized locals (or zeros)
(gdb) next                    # step into fill call site
(gdb) step                    # step *into* fill
(gdb) disassemble /m fill     # mixed C/asm view
(gdb) finish                  # return to main
(gdb) print p                 # p is a pointer (address)
(gdb) p/x p                   # hex address
(gdb) print *p                # dereference → shows struct fields
(gdb) x/32xb &buf             # dump raw bytes of buf
(gdb) watch *p                # stop when the struct contents change
(gdb) next                    # advance; triggers on writes affecting *p
(gdb) info registers          # view ABI registers (RDI/RSI/etc.)
(gdb) bt                      # call stack from main
```

**Point & takeaway**: You observe *actual bytes* at addresses, how locals live at stack offsets, how arguments flow in registers at -O0, and how pointers dereference to concrete memory.

### 2.3 Stack Canary Demo (observable protection)

`canary.c`

```c
#include <stdio.h>
#include <string.h>

static void f(const char *s){ char b[16]; strcpy(b, s); }
int main(int c, char **v){ f(c>1 ? v[1] : "short"); }
```

Build hardened vs non‑hardened:

```bash
gcc -g -O0 canary.c -o canary_no_protect
./canary_no_protect $(python3 - <<<'print("A"*200)')  # often crashes silently

gcc -g -O0 -fstack-protector-strong canary.c -o canary_protect
./canary_protect $(python3 - <<<'print("A"*200)')     # __stack_chk_fail
```

**In GDB**: `run $(python3 -c 'print("A"*200)')` → expect a call to `__stack_chk_fail`.
**Point**: You *see* the protection trigger when the local buffer is overrun.

### 2.4 Heap UAF/Double‑free (brief)

```c
char *p = malloc(16);
free(p);
// UAF:
*p = 'A';         // invalid write → ASan/Valgrind will flag
// Double free:
free(p);
```

We’ll explore with Valgrind/Sanitizers below.

### 2.5 GDB Quality‑of‑Life

* Use `list`/`disassemble /m` to correlate lines↔assembly.
* `layout asm` for an ncurses TUI.
* Deterministic ASLR for learning:

  ```
  (gdb) set disable-randomization on
  ```
* If optimized builds confuse stepping, recompile with `-O0`.

---

## 3) Ghidra: Reverse Engineering Workflow

### 3.1 Import & Analyze

1. **File → Import** `app` (or any ELF), accept defaults.
2. Open program → **Analyze** (enable default analyzers).
3. Explore **Symbol Tree** → **Functions**; open `main`.

### 3.2 Source mapping & structure

* **Decompile window**: high‑level C‑like view with inferred types.
* **Listing**: exact assembly with addresses and operands.
* **Function signature**: adjust types/arguments if Ghidra guessed wrong.
* **Stack frame**: see locals with offsets (e.g., `stack[-0x20]`).
* **XREFs**: right‑click an address/symbol → “References” to see callers/callees.

### 3.3 Patterns to recognize

* **Prologue/epilogue**; optional frame pointer omission at `-O2`.
* **PLT/GOT** calls (e.g., `printf@plt`).
* **Stack canary**: refs to `__stack_chk_fail` and TLS reads of the canary.
* **Jump tables** for `switch` (indirect jump through table).
* **Inlined functions** at `-O2` (decompiler folds small helpers).

### 3.4 Mini Ghidra Demo (using `main.c`) — What to do & see

* Rename functions (`L`) to meaningful names: `fill`, `main`.
* Apply a struct type to a stack object or pointer (Data Type Manager → define `struct S { int a; int b; }`, then apply to `p`).
* Open **Function Graph** to visualize control flow (loop, branches).
* Cross‑reference **`strcpy`** to find potential overflow sites.

**Point**: You link the **runtime view** (GDB) with the **static structure** (Ghidra), building intuition for how C constructs become code.

---

## 4) Valgrind & Sanitizers: Runtime Bug Detectors

### 4.1 Valgrind (Memcheck)

Use on **non‑optimized** builds for best line accuracy.

```bash
gcc -g -O0 uaf.c -o uaf
valgrind --leak-check=full --show-leak-kinds=all ./uaf args
```

**Expect**: precise reports (invalid read/write, use‑after‑free, leaks) with stack traces pointing to your source lines.

### 4.2 AddressSanitizer (ASan) & UBSan

Clang or GCC support:

```bash
gcc -g -O0 -fsanitize=address -fno-omit-frame-pointer uaf.c -o uaf_asan
./uaf_asan
```

**Expect**: colorful, immediate crashes on invalid memory, with **shadow memory** diagnostics and symbolized stack traces.
Add `-fsanitize=undefined` for integer overflow, out‑of‑bounds, etc.

**When to use what**:

* **ASan**: fastest dev feedback for memory bugs while you code.
* **Valgrind**: slower, but no recompilation required and good for leak hunting across libraries.

---

## 5) End‑to‑End Demo Script (put it all together)

1. Build `main.c` above with `-g -O0`.
2. **GDB**: set bp at `main`, step into `fill`, inspect `&buf`, `p`, `*p`, and registers.
3. **Ghidra**: import the same binary; rename functions, inspect stack frame, find call to `memset` and verify with XREFs.
4. Replace `strcpy` with size‑checked copy; rebuild; confirm no overflow in GDB and no `__stack_chk_fail` path in Ghidra.
5. Run **Valgrind** and **ASan** builds to ensure no invalid accesses/leaks.

**What you learn**:

* How arguments and locals map to registers/stack.
* How pointers are just addresses and dereferencing reads/writes memory at those addresses.
* How the same facts appear in three lenses: **runtime (GDB)**, **static structure (Ghidra)**, and **dynamic bug detectors (Valgrind/ASan)**.

---

## 6) Troubleshooting & Gotchas

* **Variables show `<optimized out>`**: rebuild with `-O0` or make variable `volatile` temporarily.
* **Backtraces look broken**: add `-fno-omit-frame-pointer`.
* **Stepping jumps oddly**: this is optimization/inlining; use `-O0` or step at the assembly level (`disassemble /m`).
* **Can’t see source in GDB/VS Code**: ensure `-g` and that the binary path matches your workspace.
* **ASLR changes addresses**: in GDB `set disable-randomization on` for deterministic learning.

---

## 7) Checklist: Best Practices for Module 11 Labs

* [ ] Build with `-g -O0 -fno-omit-frame-pointer` while learning.
* [ ] Turn on warnings: `-Wall -Wextra -Wshadow -Wconversion` and fix them.
* [ ] Use **GDB** to *observe*: stack frames, registers, locals, raw bytes.
* [ ] Use **Ghidra** to *structure*: functions, types, XREFs, canaries, PLT/GOT.
* [ ] Use **Valgrind/ASan** to *verify*: no leaks, no invalid reads/writes.
* [ ] Harden release builds later with `-O2 -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fPIE -pie -Wl,-z,relro,-z,now`.

---