
## 7) Labs (Hands‑On)

> Build with: `gcc -Wall -Wextra -O0 -g file.c -o file` and run from the project dir.

### Lab 9.1 — Char Reader

**Goal:** Open `hello.txt`, print all chars, handle errors.

* Create `hello.txt` with `Hello, world!\n`.
* Implement the Loop‑Until‑EOF idiom with `int c = fgetc(fp);`.
* If `fopen` fails, print `perror("hello.txt")` and return non‑zero.
* **Deliverable:** `char_reader.c`; run `./char_reader > out.txt` and verify `out.txt` contents.

### Lab 9.2 — Line Numberer

**Goal:** Read `quote.txt` line‑by‑line with `fgets`, prefix with `N:`.

* Use `char buf[1024];`, `int line = 0;` and `printf("%d: %s", ++line, buf);`.
* **Deliverable:** `line_numberer.c`; show output matches expectations.

### Lab 9.3 — Trusted `fscanf` vs Safe Parse

**Goal:** Parse `whales.txt` as `name length mass`.

* Part A: simple `fscanf` with width limits (expect count==3 per record).
* Part B (**safer**): `fgets` + `sscanf` or `strto*`; skip malformed lines.
* **Deliverable:** two programs; include a bad line to show robust behavior.

### Lab 9.4 — Text Writer

**Goal:** Use `fputc`/`fprintf`/`fputs` to generate `output.txt`.

* Confirm file truncates on each run; add a variant using `"a"` append.
* **Deliverable:** `text_writer.c`; attach `output.txt` sample.

### Lab 9.5 — Binary Bytes & Hexdump

**Goal:** Write bytes `{5,37,0,88,255,12}` to `output.bin`, then read/print them.

* Validate with `hexdump -C output.bin`.
* **Deliverable:** `write_bytes.c`, `read_bytes.c`, screenshot/snippet of hexdump.

### Lab 9.6 — Portable Integers (Big‑Endian)

**Goal:** Implement `write_u16_be` / `read_u16_be` and round‑trip a few values.

* Write values: `0x0001, 0x1234, 0xBEEF` to `ints.bin` (BE order).
* Inspect bytes with `hexdump`; read back and assert equality.
* **Deliverable:** `ints_be.c` with helper functions + test harness.

### Lab 9.7 — Error Injection & Reporting

**Goal:** Prove your error paths work.

* Try to open a missing file; print `strerror(errno)`.
* Force a short read/write (e.g., read past EOF; close stream then attempt I/O) and report via `ferror`/`feof`.
* **Deliverable:** `errors_demo.c` showing graceful messages to `stderr`.

---