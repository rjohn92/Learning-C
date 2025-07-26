# Module 2: Basic Data Types and Variables

Welcome to Module 2 of the **Comprehensive C Programming Syllabus (CNO/RE Focus)**.  
This module covers the essential building blocks of all C programs: data types and variables.

---

## What You’ll Learn

- The main data types in C: `int`, `float`, `double`, `char`, `size_t`, and more
- How to declare, initialize, and assign values to variables
- Variable *scope* and *lifetime* (local, global, static)
- Defining constants with `const` and `#define`
- Type conversions (implicit/explicit casting)
- Common pitfalls and CNO/RE-relevant best practices

---

## Why Variables Matter (Especially in CNO/RE)

- **All data in memory is ultimately variables and types.** Understanding how C stores, lays out, and manipulates variables is foundational for writing secure code *and* for analyzing binary programs.
- **Bugs and exploits often arise from misuse or misunderstanding of types, sizes, and conversions.** Off-by-one errors, signed/unsigned mismatches, and type truncation are frequent vulnerability sources.
- **Reverse engineers must recognize variable usage, type sizes, and memory layout in disassembled code.** The ability to mentally map C code to binary structure is core CNO skill.

---

## Key Topics and Examples

### 1. Data Types in C

- **Integers:** `int`, `short`, `long`, `unsigned int`, etc.
- **Floating Point:** `float`, `double`
- **Characters:** `char`
- **Sizes:** `size_t` (for memory size/counts; always use for array lengths, pointer arithmetic)
- **Type Modifiers:** `signed`, `unsigned`, `long`, `short`

```c
int age = 28;
float temp = 98.6f;
char initial = 'A';
size_t length = 16; // Preferred for memory/size variables
```
Best Practice: Always be aware of the exact width (in bytes/bits) of your types, especially for cross-platform code or security work. Use <stdint.h> for int32_t, uint8_t, etc.

```c
int x;           // Declaration (uninitialized)
x = 42;          // Assignment
int y = 100;     // Declaration + initialization
```

Security Tip: Uninitialized variables can contain junk (whatever was in that memory). Always initialize variables before use.

3. Scope and Lifetime
Local: Declared inside functions/blocks; only accessible there.

Global: Declared outside functions; accessible everywhere (use sparingly).


Static: Keeps its value between function calls, but with local or file scope.

```c
void foo() {
    int local_var = 10; // Only visible in foo()
    static int call_count = 0; // Persists across calls to foo()
}
int global_var = 5; // Visible everywhere (in this file)
```



## 4. Constants

### The `const` Keyword

- Makes a variable **read-only** after initialization (cannot be reassigned).
- Enforced by the compiler—attempting to change the value will cause a compile-time error.

```c
const float PI = 3.14159f;
```

### The `#define` Macro

- Creates a **preprocessor constant** (replaces all instances before compilation).
- No type checking; acts as a *textual substitution*.

```c
#define BUFFER_SIZE 256
```

**Best Practice:**  
Prefer `const` for typed, local constants. Use `#define` for compile-time settings, magic numbers, or cross-file flags.

---

## 5. Type Conversions and Casting

### Implicit Conversion

- The compiler automatically converts between types when needed.
- May result in **loss of precision** or unexpected behavior.

```c
float f = 5; // Implicit: int (5) is converted to float (5.0)
```

### Explicit Conversion (Casting)

- Forces a conversion from one type to another.
- Useful to clarify intent, but may still lose data (e.g., float to int truncates).

```c
int n = (int)3.9; // Explicit cast: float 3.9 becomes int 3 (truncates decimal)
```

**Common Bug:**  
Signed/unsigned mismatches and float/int conversions can cause overflows or data loss.

**Reverse Engineering Note:**  
Type mismatches (e.g., signed/unsigned, size truncations) are a common source of vulnerabilities and are often visible in disassembly.

---

## Practice / Exercises

- **Declare and initialize** all major C data types.
- **Write a function** that takes variables of different types as input and prints their values and sizes (use `sizeof`).
- **Practice scope/lifetime:** Write small functions using local, global, and static variables.
- **Try type casting:** Cast between types and observe the results (especially int/float and signed/unsigned).

---

## CNO/RE Deep Dive

- Use `sizeof()` to print type sizes; compare with memory layout in a debugger or `objdump`.
- Explore how local, global, and static variables appear in disassembly (look for `.bss`, `.data`, `.rodata` sections).
- Create small programs that trigger bugs from type overflows, truncation, or uninitialized variables—then view in GDB.

---

## Additional Resources

- [C Data Types – C Programming (GeeksforGeeks)](https://www.geeksforgeeks.org/c-data-types/)
- [Guide to Variables in C (Tutorialspoint)](https://www.tutorialspoint.com/cprogramming/c_variables.htm)
- [GNU GDB Debugger Docs](https://www.gnu.org/software/gdb/documentation/)
- [Reverse Engineering Variables in Ghidra](https://ghidra.re/)
