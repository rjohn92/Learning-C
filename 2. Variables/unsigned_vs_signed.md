# Understanding Signed vs. Unsigned Integers in C

**Module:** 2 Supplement
**Topic:** Integer Types, Overflows, and Memory Representation
**Purpose:** Build foundational understanding of how signed and unsigned values are stored, interpreted, and misused in C programming.

---

## 🧮 What Are Signed and Unsigned Integers?

In C, an `int` can be either:

* **Signed**: Can store both positive *and* negative values
* **Unsigned**: Can only store non-negative values (zero or positive)

### Example:

```c
int a = -10;          // Signed integer
unsigned int b = 10;  // Unsigned integer
```

Both are stored in binary, but the **way bits are interpreted** differs.

---

## 🧠 Why Do These Exist?

Computers work with **fixed-width binary representations**. With 32 bits:

* `unsigned int`: Values from **0 to 4,294,967,295** (2^32 - 1)
* `signed int`: Values from **-2,147,483,648 to 2,147,483,647**

Signed integers use **two's complement** to represent negative numbers. That allows fast arithmetic and consistent behavior at the hardware level.

---

## 🔄 Signed vs. Unsigned Conversion Bugs

### Silent Type Conversions

C automatically converts types when mixing signed and unsigned:

```c
int a = -1;
unsigned int b = 1;

if (a < b) {
    // You might expect this to be TRUE
    // But it's FALSE. 'a' gets cast to unsigned (wraps to 4.2 billion)
}
```

### Underflow and Wraparound

```c
unsigned int u = 0;
u--;  // Now u == 4,294,967,295
```

```c
int i = 2147483647;
i++;  // Now i == -2147483648 (wraps around)
```

This is how many buffer overflow vulnerabilities start.

---

## 📏 Size and Range Comparison (Typical 32-bit Platform)

| Type           | Min Value                  | Max Value                  |
| -------------- | -------------------------- | -------------------------- |
| `int`          | -2,147,483,648             | 2,147,483,647              |
| `unsigned int` | 0                          | 4,294,967,295              |
| `int8_t`       | -128                       | 127                        |
| `uint8_t`      | 0                          | 255                        |
| `int64_t`      | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807  |
| `uint64_t`     | 0                          | 18,446,744,073,709,551,615 |

> Use `<stdint.h>` for exact-width types like `uint8_t`, `int32_t`, etc.

---

## 🛡️ Best Practices

* Use `unsigned` **only when negatives are truly invalid** (e.g., byte counts, indexes)
* Avoid mixing signed and unsigned types in comparisons
* Use `size_t` for memory sizes and loop counters
* Prefer `<stdint.h>` types (`int32_t`, `uint32_t`) for clarity and portability
* Use `-Wall -Wextra -Wsign-compare` when compiling with `gcc` to catch bugs

---

## 🔬 CNO and Reverse Engineering Relevance

* **Integer overflows** from signed/unsigned mixups are a **classic vulnerability**
* Many CTF and exploit challenges revolve around bypassing logic via integer promotion
* Reverse engineers must infer variable types based on value ranges and disassembly patterns
* Common sections to inspect: `.data`, `.bss`, `.rodata` for type layout clues

---

## 🧪 Practice Exercise

```c
#include <stdio.h>

int main() {
    int x = -5;
    unsigned int y = 10;

    if (x < y)
        printf("x is less than y\n");
    else
        printf("This might surprise you.\n");

    unsigned int a = 0;
    a--;
    printf("Unsigned wraparound: %u\n", a);

    return 0;
}
```

Try compiling with `gcc -Wall -Wextra` and observe warnings.

---

## 📚 Additional Reading

* [Integer Overflows in C – CERT Guide](https://wiki.sei.cmu.edu/confluence/display/c/INT)
* [C Two's Complement Explained](https://en.wikipedia.org/wiki/Two%27s_complement)
* [ISO C99 Standard - Integer Promotion Rules](https://port70.net/~nsz/c/c99/n1256.html#6.3.1.8)

---

## ✅ Summary

| Concept              | Key Point                                         |
| -------------------- | ------------------------------------------------- |
| Signed int           | Can go negative                                   |
| Unsigned int         | Can’t go negative, wraps instead                  |
| Implicit conversions | May cause logic bugs                              |
| Underflow/Overflow   | Common in exploits                                |
| RE/CNO relevance     | Critical for vulnerability analysis and reversing |

---

Signed vs. unsigned may seem small, but mastering it separates beginner programmers from system-level professionals and exploit developers. Don’t skip it.
