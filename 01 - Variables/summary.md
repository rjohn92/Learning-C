# Module 2 Takeaways: Data Types, Casting, and Scope in C

* **Casting between types (e.g., `float` to `int`)** results in truncation and loss of precision. This can lead to subtle bugs and security issues if not handled carefully.
* **Unsigned integers** (`unsigned int`) can represent much larger positive values than signed integers. However, when casting between signed and unsigned types, or performing arithmetic that exceeds their bounds, **wraparound** can occur (values "loop around" to the other end of the range).
* **Static local variables** inside functions retain their value between calls, persisting for the entire runtime of the program. This is useful for counting or remembering state across function invocations, but not for storing per-call values.
* **Local (non-static) variables** are reinitialized every time the function is called.
* **`printf` format specifiers:**

  * `%d` for `int`
  * `%f` / `%.2f` for `float`/`double` (use `%.2f` for two decimal places)
  * `%c` for `char`
  * `%zu` for `size_t`
    `const float` is printed just like any other float.
* **Security note:** Many vulnerabilities in C programs come from careless type conversions and wraparound bugs. Always check for compiler warnings and understand the range of your types.
* **Type sizes and system architecture:**

  * Some types (especially `long`, `size_t`) change size depending on whether your computer is 32-bit or 64-bit. This affects how big a value you can store and can explain differences between systems or sample outputs you find online.
  * You can check your architecture with `uname -m` on Linux (`x86_64` = 64-bit, `i386`/`i686` = 32-bit).
  * In C, printing `sizeof(int)` or `sizeof(size_t)` will show you the size in **bytes** on your system. Remember: 1 byte = 8 bits.
  * If your program needs to handle very large numbers, or if you see weird results between systems, **check your type sizes first**.
* **System bitness affects code, bugs, and even vulnerabilities:** Binary compatibility and the limits of types in C are determined by your hardware and OS. This is crucial for security, reverse engineering, and robust C development.

*Mastering these fundamentals is essential not just for correct C programs, but for writing secure, robust code and for reverse engineering binaries in CNO work. Even at the level of basic variables and types, the underlying hardware matters!*
