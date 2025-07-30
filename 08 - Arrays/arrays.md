# Arrays in C: A Pragmatic Technical Guide

---

## 1. Introduction

Arrays are a foundational feature in C, allowing you to store multiple values of the same type in contiguous memory. Explanation:

Contiguous memory means that all elements of the array are stored right next to each other in a single, unbroken block of memory, without gaps.

What does this actually mean in C?
If you declare int a[4];, the four ints are laid out in memory one after the other.

If the address of a[0] is 0x1000 and sizeof(int) is 4 bytes, then:

a[1] is at 0x1004

a[2] is at 0x1008

a[3] is at 0x100C

Why does this matter?
Enables fast, constant-time access by index: the address of a[i] is simply the start address plus i * sizeof(int).

Required for pointer arithmetic and passing arrays to functions.

Critical for security: buffer overflows exploit this property to overwrite adjacent memory.

Summary:

Contiguous memory = elements are stored sequentially, with no gaps, enabling predictable memory layout and access in C arrays. While they look simple, their implementation and usage have nuances that every serious C programmer must master—especially for systems programming, reverse engineering, or CNO work.

---

## 2. Array Declaration & Basic Usage

**Syntax:**

```c
<type> <array_name>[<size>];
```

Example:

```c
int a[4]; // array of 4 ints
float f[10]; // array of 10 floats
```

### Assignment & Access

* Indexing starts at `0` (C standard).
* Assign and access values using `[ ]`:

```c
float f[4];
f[0] = 3.14159;
f[1] = 1.41421;
f[2] = 1.61803;
f[3] = 2.71828;

for (int i = 0; i < 4; i++) {
    printf("%f\n", f[i]);
}
```

* **Array size is fixed at declaration** (no dynamic resizing—use dynamic allocation for that).

---

## 3. Array Length: The `sizeof` Trick

C does *not* store array length. Programmers must track it manually.

**In the declaring scope:**

```c
int x[12];
printf("%zu\n", sizeof x);            // Total bytes
printf("%zu\n", sizeof(int));         // Bytes per element
printf("%zu\n", sizeof x / sizeof(int)); // Number of elements
```

**Caveat:**

* This works only in the same scope as the declaration. If you pass the array to a function, it decays to a pointer, and `sizeof` gives the size of the pointer (usually 8 bytes on 64-bit systems), not the whole array.

```c
void foo(int x[12]) {
    printf("%zu\n", sizeof x);            // 8 bytes (pointer size)
    printf("%zu\n", sizeof x / sizeof(int)); // 2 (incorrect)
}
```

* **Best practice:** always pass the array length as a separate parameter.

---

## 4. Array Initializers

You can assign initial values at declaration:

```c
int a[5] = {22, 37, 3490, 18, 95};
```

* Too many initializers: compiler error.
* Too few: remaining elements are zero-initialized.

```c
int a[5] = {22, 37, 3490}; // a == {22, 37, 3490, 0, 0}
int a[100] = {0}; // all elements zero
```

**Designated initializers (C99+):**

```c
int a[10] = {0, 11, 22, [5]=55, 66, 77};
// Result: 0 11 22 0 0 55 66 77 0 0

#define COUNT 5
int b[COUNT] = {[COUNT-3]=3, 2, 1}; // 0 0 3 2 1
```

**Omitting the size:**

```c
int a[] = {22, 37, 3490}; // size inferred (3)
```

---

## 5. Out of Bounds Access (Undefined Behavior)

C does **not** check bounds at runtime:

```c
int a[5] = {22, 37, 3490, 18, 95};
for (int i = 0; i < 10; i++) {
    printf("%d\n", a[i]); // prints garbage after the 5th element
}
```

* Accessing out of bounds is undefined behavior: could return garbage, crash, or corrupt memory.
* **Rule:** Never access past the array’s declared bounds.

---

## 6. Multidimensional Arrays

```c
int a[10];         // 1D array
int b[2][7];       // 2D array
int c[4][5][6];    // 3D array
```

* Stored in **row-major order**.
* Initialization example:

```c
int a[2][5] = {
    {0, 1, 2, 3, 4},
    {5, 6, 7, 8, 9}
};
```

* Access example:

```c
for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 5; col++) {
        printf("(%d,%d) = %d\n", row, col, a[row][col]);
    }
}
```

* **Designated initializers:**

```c
int id[3][3] = {[0][0]=1, [1][1]=1, [2][2]=1}; // identity matrix
```

---

## 7. Arrays vs. Pointers: How They Relate

* In most expressions, array names **decay** to pointers to their first element.
* `a` and `&a[0]` are equivalent in most contexts.
* Example:

```c
int a[5] = {11, 22, 33, 44, 55};
int *p = &a[0]; // explicit
p = a;         // equivalent
printf("%d\n", *p); // prints 11
```

* Passing an array to a function actually passes a pointer:

```c
void f(int *a, int len);
void g(int a[], int len);
void h(int a[5], int len);
// All are equivalent: they receive int *
```

* **You must always pass the length separately.**

---

## 8. Modifying Arrays via Functions

Arrays (as function parameters) are passed by reference:

```c
void double_array(int *a, int len) {
    for (int i = 0; i < len; i++) a[i] *= 2;
}

int main(void) {
    int x[5] = {1, 2, 3, 4, 5};
    double_array(x, 5);
    // x is now {2, 4, 6, 8, 10}
}
```

Changes made to the array in the function **are visible in the caller**.

---

## 9. Multidimensional Arrays in Functions

All dimensions (except the first) must be specified:

```c
void print_2D(int a[][3]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int main(void) {
    int x[2][3] = { {1,2,3}, {4,5,6} };
    print_2D(x);
}
```

* The compiler needs to know the size of all but the first dimension for correct address arithmetic.

---

## 10. Arrays: Practical Summary

* **Fixed size**: Must be known at compile time (for stack arrays)
* **No bounds checking**: Programmer is responsible
* **Decay to pointers**: In most contexts
* **Pass length explicitly**: Always
* **Can be modified in functions**: Arrays are passed by reference

---

## 11. Security and Best Practices Notes

* **Buffer overflows**: Always check bounds manually; never trust user input as an array index.
* **Stack vs. heap**: Use `malloc`/`free` for dynamically sized arrays; stack arrays are fast but limited in size.
* **Out-of-bounds bugs**: These are the cause of the majority of memory corruption and remote code execution vulnerabilities in C code.

---

## 12. References

* ISO/IEC 9899:2018 (C18 Standard)
* Beej’s Guide to C Programming
* "The C Programming Language" (Kernighan & Ritchie)
* CERT C Secure Coding Standard

---

*This document is designed for technical self-study, security, and professional software development. It omits didactic or academic hand-waving—refer to source code and standards for further details.*
