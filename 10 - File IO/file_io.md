# Module 9 — File Input/Output (Lab Notes)

> **Scope:** Practical, lab‑oriented notes for working with C file/stream I/O (text & binary), including safe parsing, error handling, and portability pitfalls (EOF, struct padding, endianness).

---

## 0) Learning Objectives

By the end of this module you should be able to:

* Explain what a `FILE *` stream is and use the standard streams `stdin`, `stdout`, `stderr`.
* Open/close files with `fopen()/fclose()` and report errors correctly.
* Read text a **char** at a time (`fgetc`), and a **line** at a time (`fgets`).
* Write text with `fputc`, `fputs`, and `fprintf`.
* Use `fscanf` **safely** (or replace with `fgets` + `strto*` parsing for untrusted input).
* Read/write **binary** data with `fread`/`fwrite`.
* Describe and handle portability hazards: **EOF is `int`**, newline translation, **struct padding**, **endianness**, and floating‑point representation.
* Validate outputs using shell redirection and hex‑dump tools.

---

## 1) Quick Glossary

* **Stream:** Abstract source/sink of bytes. Files are just one kind; terminals, pipes, sockets also look like streams.
* **`FILE *`:** Opaque handle that tracks buffering, position, and OS file descriptor.
* **Text vs Binary:** Text streams may translate newlines; binary streams are raw bytes (no translation).
* **EOF:** End‑of‑file indicator; many functions return `EOF` (often −1) or 0‑count to signal no more data.
* **Endianness:** Byte order of multi‑byte integers in memory/streams (little vs big).

---

## 2) Standard Streams & Redirection

| Name     | Purpose                         | Typical default |
| -------- | ------------------------------- | --------------- |
| `stdin`  | Standard input                  | Keyboard        |
| `stdout` | Standard output (normal output) | Screen          |
| `stderr` | Standard error (diagnostics)    | Screen          |

**Why two outputs?** So the shell can redirect them separately:

```sh
./prog >out.txt 2>err.txt      # stdout→file, stderr→file
./prog >out.txt 2>&1           # merge stderr into stdout
cat input.txt | ./prog         # stdin comes from a pipe
```

**Rule:** Print human‑visible results to `stdout`; print errors to `stderr`.

---

## 3) Core APIs (Cheat Sheet)

### Opening/closing

```c
FILE *fopen(const char *path, const char *mode);  // returns NULL on error
int fclose(FILE *fp);                              // returns 0 on success
```

**Common `mode` values:**

* Text: `"r"` read, `"w"` write (truncate), `"a"` append, `"r+"` read/write, `"w+"` read/write (truncate), `"a+"` read/append
* Binary: add `b` → `"rb"`, `"wb"`, `"ab"`, etc.

### Text input

```c
int fgetc(FILE *fp);        // returns unsigned char cast to int, or EOF
char *fgets(char *s, int n, FILE *fp); // reads up to n-1 chars; NUL terminates; NULL on EOF/error
int fscanf(FILE *fp, const char *fmt, ...); // returns number of items scanned or EOF
```

### Text output

```c
int fputc(int c, FILE *fp);
int fputs(const char *s, FILE *fp);
int fprintf(FILE *fp, const char *fmt, ...);
```

### Binary I/O

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);   // returns items read
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp); // returns items written
```

### Error handling & state

```c
int feof(FILE *fp);     // nonzero if EOF seen
int ferror(FILE *fp);   // nonzero if error seen
void clearerr(FILE *fp);
#include <errno.h>
#include <string.h>
perror("msg");         // prints msg: <strerror(errno)> to stderr
```

---

## 4) Idioms & Best Practices

* **Always check return values** of `fopen`, `fgets`, `fread`/`fwrite`, etc. On failure, print to `stderr` and exit or recover.
* **EOF handling:** store `fgetc` result in an `int` and compare to `EOF`.
* **Safe scanning:** avoid bare `%s` in `scanf`/`fscanf`; if you must, limit width: `"%1023s"` into a 1024‑byte buffer. Prefer `fgets` then `strtol`/`strtod` to parse.
* **Buffers:** with `fgets`, pass `sizeof buf` (not a magic number). Keep lines ≤ buffer size (portable text files end with newline).
* **Text vs binary:** on Windows, open binary files with `b` to avoid newline translation.
* **Flush/close:** `fclose` flushes buffers; `fflush(fp)` flushes without closing (useful for logs or interactive prompts).
* **Portability:** do **not** `fwrite` raw structs intended for cross‑platform interchange; serialize fields explicitly in a defined byte order.

---

## 5) Worked Examples (Minimal, Buildable)

### 5.1 Read a file char‑by‑char (prints to stdout)

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) { fprintf(stderr, "fopen: %s\n", strerror(errno)); return 1; }

    int c;
    while ((c = fgetc(fp)) != EOF) putchar(c);

    if (ferror(fp)) fprintf(stderr, "read error\n");
    fclose(fp);
}
```

### 5.2 Read a file line‑by‑line with line numbers

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("quote.txt", "r");
    if (!fp) { fprintf(stderr, "fopen: %s\n", strerror(errno)); return 1; }

    char buf[1024];
    int line = 0;
    while (fgets(buf, sizeof buf, fp)) {
        printf("%d: %s", ++line, buf); // buf already contains newline if present
    }
    if (ferror(fp)) fprintf(stderr, "read error\n");
    fclose(fp);
}
```

### 5.3 Formatted read (trusted file) vs safe parse (untrusted)

**Trusted (simple):**

```c
// whales.txt: name length(m) mass(tonnes)
#include <stdio.h>
int main(void){
    FILE *fp = fopen("whales.txt", "r");
    if(!fp){perror("fopen"); return 1;}
    char name[1024]; float length; int mass;
    while (fscanf(fp, "%1023s %f %d", name, &length, &mass) == 3) {
        printf("%s whale, %d tonnes, %.1f meters\n", name, mass, length);
    }
    fclose(fp);
}
```

**Safer (untrusted):**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *fp = fopen("whales.txt", "r");
    if(!fp){perror("fopen"); return 1;}
    char line[1024], name[1024];
    while (fgets(line, sizeof line, fp)) {
        char *p = line; double length; long mass;
        if (sscanf(p, "%1023s %lf %ld", name, &length, &mass) == 3) {
            printf("%s whale, %ld tonnes, %.1f meters\n", name, mass, length);
        } // else: skip malformed line
    }
    fclose(fp);
}
```

### 5.4 Write text

```c
#include <stdio.h>
int main(void){
    FILE *fp = fopen("output.txt", "w");
    if(!fp){perror("fopen"); return 1;}
    fputc('B', fp); fputc('\n', fp);
    int x = 32; fprintf(fp, "x = %d\n", x);
    fputs("Hello, world!\n", fp);
    fclose(fp);
}
```

### 5.5 Write & read binary bytes

```c
// write_bytes.c
#include <stdio.h>
int main(void){
    unsigned char bytes[6] = {5, 37, 0, 88, 255, 12};
    FILE *fp = fopen("output.bin", "wb"); if(!fp){perror("fopen"); return 1;}
    size_t n = fwrite(bytes, sizeof bytes[0], 6, fp);
    if (n != 6) { fprintf(stderr, "short write\n"); }
    fclose(fp);
}
```

```c
// read_bytes.c
#include <stdio.h>
int main(void){
    FILE *fp = fopen("output.bin", "rb"); if(!fp){perror("fopen"); return 1;}
    unsigned char c;
    while (fread(&c, sizeof c, 1, fp) == 1) printf("%u\n", c);
    fclose(fp);
}
```

**Inspect with hexdump:**

```sh
gcc -Wall -Wextra -O0 -g write_bytes.c -o write_bytes
./write_bytes
hexdump -C output.bin
# Expect: 05 25 00 58 ff 0c
```

---

## 6) Portability Hazards (Structs & Numbers)

### 6.1 Struct padding

Compilers may insert padding between fields for alignment → `sizeof(struct)` varies across compilers/architectures/build flags. **Avoid** `fwrite(&s, sizeof s, 1, fp)` for interchange files. Serialize each field explicitly.

### 6.2 Endianness

Multi‑byte integers differ in byte order (little vs big). If you `fwrite(&v, sizeof v, 1, fp)`, the on‑disk byte order will match the host’s endianness — **not portable**.

**Write a 16‑bit big‑endian helper:**

```c
#include <stdint.h>
int write_u16_be(FILE *fp, uint16_t v){
    unsigned char b[2] = { (unsigned char)(v>>8), (unsigned char)(v&0xFF) };
    return fwrite(b, 1, 2, fp) == 2 ? 0 : -1;
}
```

**Read a 16‑bit big‑endian helper:**

```c
int read_u16_be(FILE *fp, uint16_t *out){
    unsigned char b[2];
    if (fread(b,1,2,fp) != 2) return -1;
    *out = (uint16_t)((b[0]<<8) | b[1]);
    return 0;
}
```

Apply the same idea for 32‑/64‑bit integers. Define a **file format** and stick to it.

### 6.3 Floating point

Binary layouts are usually IEEE‑754 but not guaranteed everywhere; textual serialization (`fprintf`/`strtod`) or well‑defined binary formats are safer.

---


## 8) Validation Checklist

* [ ] All `fopen` calls are checked (`if (!fp) { perror(...); return 1; }`).
* [ ] `fgetc` results stored in `int` and compared to `EOF`.
* [ ] No unbounded `%s` in any `scanf`‑style call.
* [ ] `fgets` size uses `sizeof buf`.
* [ ] Text vs binary modes chosen correctly (use `b` for binary on Windows).
* [ ] `fclose` called on all opened streams (even on error paths).
* [ ] Binary round‑trip shows expected hex dump.
* [ ] Big‑endian helpers produce stable, cross‑platform bytes.

---

## 9) Common Pitfalls & Fixes

* **Symptom:** Infinite loop on `fgets`/`fread` → **Cause:** not checking return value properly. **Fix:** stop on `NULL`/0.
* **Symptom:** Garbled text on Windows → **Cause:** wrong text/binary mode. **Fix:** use `"rb"/"wb"` for binary.
* **Symptom:** Buffer overflow with `scanf("%s")` → **Fix:** width limit or `fgets` + manual parse.
* **Symptom:** Wrong numbers when sharing files across machines → **Cause:** endianness. **Fix:** normalize byte order.
* **Symptom:** Extra blank lines when printing lines → **Cause:** line already has `\n`. **Fix:** don’t add another unless missing.

---

## 10) Tooling Tips

* **Compiler flags:** `-Wall -Wextra -Wpedantic -O0 -g` while learning.
* **Hex dump:** `hexdump -C file.bin` or `xxd -g1 file.bin`.
* **strace (Linux):** `strace -e read,write,openat ./prog` to see syscalls.
* **gdb:** set breakpoints around I/O to inspect buffers and return values.

---

## 11) Appendix — `fopen` Modes Quick Table

| Mode | Meaning (Text)                  | Binary variant |
| ---- | ------------------------------- | -------------- |
| `r`  | read existing                   | `rb`           |
| `w`  | write (truncate/create)         | `wb`           |
| `a`  | append (create if missing)      | `ab`           |
| `r+` | read/write (must exist)         | `rb+`          |
| `w+` | read/write (truncate/create)    | `wb+`          |
| `a+` | read/append (create if missing) | `ab+`          |

---

### End Note

For interoperable binary files, **define a format** (byte order, field sizes, text encoding) and **serialize explicitly**. Future‑you (and other languages) will thank present‑you.
