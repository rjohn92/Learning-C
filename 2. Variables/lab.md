# Lab: Working With C Data Types, Variables, and Memory

**Module:** 2 – Basic Data Types and Variables
**Skill Level:** Beginner
**Estimated Time:** 1.5–2 hours
**Objective:** Practice using fundamental C data types, constants, and scoping rules. Begin to connect type layout with memory and reverse engineering concepts.

---

## 🧪 Lab 1: Declare, Initialize, and Print Variables

### Instructions

1. Create a file named `lab2_variables.c`
2. Declare and initialize the following:

   * An `int` with any value
   * A `float` with a decimal value
   * A `char` with a letter
   * A `size_t` with a length
   * A `const` float for π
   * A `#define` value for BUFFER\_SIZE
3. Print each variable using `printf()`
4. Also print their sizes using `sizeof()`

### Example Snippet

```c
#include <stdio.h>

#define BUFFER_SIZE 256

int main() {
    int age = 30;
    float temp = 98.6f;
    char initial = 'J';
    size_t count = 100;
    const float PI = 3.14159f;

    printf("Age: %d (size: %zu bytes)\n", age, sizeof(age));
    printf("Temp: %.2f (size: %zu bytes)\n", temp, sizeof(temp));
    printf("Initial: %c (size: %zu bytes)\n", initial, sizeof(initial));
    printf("Count: %zu (size: %zu bytes)\n", count, sizeof(count));
    printf("PI: %.5f\n", PI);
    printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);

    return 0;
}
```

### 🧬 Questions

* What’s the difference in output between `sizeof(char)` and `sizeof(size_t)`?
* What happens if you try to modify a `const` variable? A `#define`?

---

## 🧪 Lab 2: Scope and Lifetime

### Instructions

1. Create a new file: `lab2_scope.c`
2. Implement:

   * A global variable
   * A local variable inside `main()`
   * A static variable inside a helper function that gets called multiple times
3. Call the helper function 3+ times and observe how the static variable behaves.

### Example Snippet

```c
#include <stdio.h>

int global_counter = 0;

void count_calls() {
    static int calls = 0;
    calls++;
    printf("This function has been called %d times.\n", calls);
}

int main() {
    int local = 42;
    printf("Global: %d\n", global_counter);
    printf("Local: %d\n", local);

    for (int i = 0; i < 3; i++) {
        count_calls();
    }

    return 0;
}
```

### 🧬 Questions

* What happens if you remove the `static` keyword?
* Where in memory do global/static variables live?

---

## 🧪 Lab 3: Type Conversion and Casting

### Instructions

1. Create `lab2_casting.c`
2. Declare:

   * A float, assign it a decimal number like `5.87`
   * An int, assign it the float (with and without casting)
3. Try converting:

   * `float` → `int` (observe truncation)
   * `unsigned int` → `signed int` with a large value (observe wraparound)

### Example Snippet

```c
#include <stdio.h>

int main() {
    float f = 5.87f;
    int i1 = f;              // Implicit cast
    int i2 = (int)f;         // Explicit cast

    unsigned int u = 4294967295; // max for 32-bit unsigned
    int s = u; // what happens?

    printf("Original float: %.2f\n", f);
    printf("Implicit int: %d\n", i1);
    printf("Explicit int: %d\n", i2);
    printf("Unsigned: %u, Interpreted as signed: %d\n", u, s);

    return 0;
}
```

### 🧬 Questions

* What’s the difference between implicit and explicit casting?
* When does data loss happen?
* How can this be dangerous in security-critical software?

---

## 🔬 Bonus CNO/RE Challenge: Disassembly Walkthrough

### Instructions

1. Compile any of the above programs with debug symbols:

   ```bash
   gcc -Wall -g lab2_variables.c -o lab2_variables
   ```

2. Open in `gdb`:

   ```bash
   gdb ./lab2_variables
   ```

   Set breakpoints and use:

   * `info locals`
   * `print sizeof(...)`
   * `x/4xb &variable`

3. Disassemble with:

   ```bash
   objdump -d lab2_variables > disasm.txt
   ```

   Try to identify where your variables appear in `.data`, `.bss`, or `.rodata` sections.

4. (Optional) Open in **Ghidra**, locate the variable declarations, and note how `const` and `static` affect layout and visibility.

---

## ✅ Checkpoint Review

| Task                                 | Done? |
| ------------------------------------ | ----- |
| Declared & printed all major C types | ☑     |
| Used `sizeof()` to explore memory    | ☑     |
| Tested scope & static behavior       | ☑     |
| Practiced casting between types      | ☑     |
| Opened a binary in GDB or objdump    | ☑     |
| Understood how memory layout works   | ☑     |

---

## Submission / Write-Up (Optional)

If you're using GitHub or journaling your self-study:

* Create a `lab2/` folder
* Save your `.c` files and screenshots of `gdb` or `objdump`
* Write a short markdown file: `lab2_writeup.md` with answers to each question and insights from your RE exploration
