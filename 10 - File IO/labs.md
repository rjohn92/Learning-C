
## 7) Labs (Hands‑On)

> Build with: `gcc -Wall -Wextra -O0 -g file.c -o file` and run from the project dir.

### Lab 10.1 — Char Reader

**Goal:** Open `hello.txt`, print all chars, handle errors.

* Create `hello.txt` with `Hello, world!\n`.
* Implement the Loop‑Until‑EOF idiom with `int c = fgetc(fp);`.
* If `fopen` fails, print `perror("hello.txt")` and return non‑zero.




```c
#include <stdio.h>
static void copy_all(FILE *fp) {
    // TODO: Implement Loop-Until-EOF with:
    //   int c; while ((c = fgetc(fp)) != EOF) { putchar(c); }
    // Also handle errors on stdout (putchar) and on the stream (ferror(fp)).
    (void)fp; // remove after implementing
}

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) {
        // TODO: Per lab, call perror("hello.txt") and return non-zero
        return 1; // placeholder
    }

    copy_all(fp);

    // Optional: check ferror(fp) and perror if needed
    fclose(fp);
    return 0;
}
```

* **Deliverable:** `char_reader.c`; run `./char_reader > out.txt` and verify `out.txt` contents.

### Lab 10.2 — Line Numberer

**Goal:** Read `quote.txt` line‑by‑line with `fgets`, prefix with `N:`.

* Use `char buf[1024];`, `int line = 0;` and `printf("%d: %s", ++line, buf);`.
```c
// line_numberer.c
// Build: gcc -Wall -Wextra -O0 -g line_numberer.c -o line_numberer
// Run:   ./line_numberer < quote.txt
#include <stdio.h>

static void number_lines(FILE *in) {
    // TODO:
    //   char buf[1024];
    //   int line = 0;
    //   while (fgets(buf, sizeof buf, in)) {
    //       printf("%d: %s", ++line, buf);
    //   }
    (void)in; // remove after implementing
}

int main(void) {
    number_lines(stdin);
    return 0;
}


* **Deliverable:** `line_numberer.c`; show output matches expectations.

### Lab 10.3 — Trusted `fscanf` vs Safe Parse

**Goal:** Parse `whales.txt` as `name length mass`.

* Part A: simple `fscanf` with width limits (expect count==3 per record).
* Part B (**safer**): `fgets` + `sscanf` or `strto*`; skip malformed lines.
```c

// whales_scan_trusted.c
// Build: gcc -Wall -Wextra -O0 -g whales_scan_trusted.c -o whales_scan_trusted
// Run:   ./whales_scan_trusted < whales.txt
#include <stdio.h>

int main(void) {
    // Expected format per line: name length mass
    // e.g., "orca 6.5 5400"
    char name[64];       // width-limited destination
    double length = 0.0;
    double mass = 0.0;

    // TODO:
    //   while (fscanf(stdin, "%63s %lf %lf", name, &length, &mass) == 3) {
    //       printf("%s %.2f %.1f\n", name, length, mass);
    //   }
    //
    // Optionally detect malformed lines (return != 3) and report.

    (void)name; (void)length; (void)mass; // remove after implementing
    return 0;
}

* **Deliverable:** two programs; include a bad line to show robust behavior.

### Lab 10.4 — Text Writer

**Goal:** Use `fputc`/`fprintf`/`fputs` to generate `output.txt`.

* Confirm file truncates on each run; add a variant using `"a"` append.
```c

// text_writer.c
// Build: gcc -Wall -Wextra -O0 -g text_writer.c -o text_writer
// Run:   ./text_writer w   # truncates
//        ./text_writer a   # appends
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    const char *mode = "w";
    if (argc > 1 && strcmp(argv[1], "a") == 0) mode = "a";

    FILE *fp = fopen("output.txt", mode);
    if (!fp) {
        // TODO: perror("output.txt"); return non-zero
        return 1; // placeholder
    }

    // TODO: Write with fputc/fputs/fprintf, e.g.:
    //   fputs("First line\n", fp);
    //   fprintf(fp, "Number: %d\n", 42);
    //   fputc('\n', fp);

    // Optional: check errors with ferror(fp)
    fclose(fp);
    return 0;
}

* **Deliverable:** `text_writer.c`; attach `output.txt` sample.

### Lab 10.5 — Binary Bytes & Hexdump

**Goal:** Write bytes `{5,37,0,88,255,12}` to `output.bin`, then read/print them.

* Validate with `hexdump -C output.bin`.
```c

// write_bytes.c
// Build: gcc -Wall -Wextra -O0 -g write_bytes.c -o write_bytes
// Run:   ./write_bytes && hexdump -C output.bin
#include <stdio.h>
#include <stdint.h>

int main(void) {
    const uint8_t bytes[] = {5, 37, 0, 88, 255, 12};
    FILE *fp = fopen("output.bin", "wb");
    if (!fp) {
        // TODO: perror("output.bin"); return non-zero
        return 1;
    }

    // TODO: Write all bytes:
    //   size_t n = fwrite(bytes, 1, sizeof bytes, fp);
    //   if (n != sizeof bytes) { /* handle short write via perror/ferror */ }

    fclose(fp);
    return 0;
}

```

* **Deliverable:** `write_bytes.c`, `read_bytes.c`, screenshot/snippet of hexdump.

### Lab 10.6 — Portable Integers (Big‑Endian)

**Goal:** Implement `write_u16_be` / `read_u16_be` and round‑trip a few values.

* Write values: `0x0001, 0x1234, 0xBEEF` to `ints.bin` (BE order).
* Inspect bytes with `hexdump`; read back and assert equality.

```c

// ints_be.c
// Build: gcc -Wall -Wextra -O0 -g ints_be.c -o ints_be
// Run:   ./ints_be && hexdump -C ints.bin && ./ints_be read
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static int write_u16_be(uint16_t v, FILE *fp) {
    // TODO: split into two bytes in big-endian order and fputc them:
    //   uint8_t hi = (uint8_t)(v >> 8);
    //   uint8_t lo = (uint8_t)(v & 0xFF);
    //   if (fputc(hi, fp) == EOF || fputc(lo, fp) == EOF) return -1;
    (void)v; (void)fp; // remove after implementing
    return 0;
}

static int read_u16_be(uint16_t *out, FILE *fp) {
    // TODO: read two bytes with fgetc; on EOF return -1; combine into uint16_t
    (void)out; (void)fp; // remove after implementing
    return 0;
}

static int write_demo(void) {
    FILE *fp = fopen("ints.bin", "wb");
    if (!fp) { perror("ints.bin"); return 1; }

    // Values: 0x0001, 0x1234, 0xBEEF
    uint16_t vals[] = {0x0001u, 0x1234u, 0xBEEFu};

    // TODO: loop and write each with write_u16_be(...)

    fclose(fp);
    return 0;
}

static int read_demo(void) {
    FILE *fp = fopen("ints.bin", "rb");
    if (!fp) { perror("ints.bin"); return 1; }

    // TODO: read in a loop with read_u16_be and print each as 0x%04X

    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "read") == 0) {
        return read_demo();
    }
    return write_demo();
}
```
* **Deliverable:** `ints_be.c` with helper functions + test harness.

### Lab 10.7 — Error Injection & Reporting

**Goal:** Prove your error paths work.

* Try to open a missing file; print `strerror(errno)`.
* Force a short read/write (e.g., read past EOF; close stream then attempt I/O) and report via `ferror`/`feof`.
```c

// errors_demo.c
// Build: gcc -Wall -Wextra -O0 -g errors_demo.c -o errors_demo
// Run:   ./errors_demo
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void missing_file_demo(void) {
    // TODO: Try to open a file that doesn't exist.
    //   FILE *fp = fopen("nope_does_not_exist.txt", "r");
    //   if (!fp) fprintf(stderr, "Open failed: %s\n", strerror(errno));
}

static void short_io_and_flags_demo(void) {
    // TODO:
    // 1) Open a small text file for reading.
    // 2) Read past EOF, then check feof(fp) and ferror(fp).
    // 3) Open a file for writing, fclose it, then attempt fputc to provoke error.
    // 4) Detect and report with ferror(fp), then clear with clearerr(fp) (optional).
    (void)errno; // remove after implementing
}

int main(void) {
    missing_file_demo();
    short_io_and_flags_demo();
    return 0;
}

```
* **Deliverable:** `errors_demo.c` showing graceful messages to `stderr`.

---