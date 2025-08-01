# 4. Functions in C

Functions in C are similar to those in most programming languages, but with some strict requirements and behaviors unique to the language. This section covers definitions, parameter handling, return values, prototypes, and the importance of explicitly declaring types.

---

## Function Basics

A function in C is a named block of code that can accept arguments and optionally return a value.
**Important:** Both argument types and the return type must be predeclared—this is required by the language.

**Example:** A simple function that takes an `int` and returns an `int`:

```c
#include <stdio.h>

int plus_one(int n)  // Definition: takes an int, returns an int
{
    return n + 1;
}
```

* The `int` before `plus_one` is the **return type**.
* The `int n` inside the parentheses declares a single **parameter** (a local variable inside the function, into which the argument is copied).

### Main Function Example

Calling the function from `main()`:

```c
int main(void)
{
    int i = 10, j;

    j = plus_one(i);  // Function call

    printf("i + 1 is %d\n", j);
}
```

**Note:**

* The function `plus_one` must be *defined before* it is called in `main()`, or at least *declared* using a function prototype.
* `main()` itself is a function: it returns `int` and takes no arguments, indicated by `void`.

---

## Functions with No Arguments or Return Value

You can declare a function that takes no arguments (use `void` as the parameter list) and/or returns nothing (use `void` as the return type).

**Example:**

```c
#include <stdio.h>

// No arguments, no return value
void hello(void)
{
    printf("Hello, world!\n");
}

int main(void)
{
    hello();  // Prints "Hello, world!"
}
```

---

## 4.1 Passing by Value

**Key Principle:**
*All arguments in C are passed by value*.
This means:

* When you call a function, the value of each argument is **copied** into the corresponding parameter variable.
* The function operates on this local copy, not the original variable.

**Example:**

```c
#include <stdio.h>

void increment(int a)
{
    a++;
}

int main(void)
{
    int i = 10;

    increment(i);

    printf("i == %d\n", i);  // Output: 10
}
```

* Even though `a` is incremented in the function, `i` remains unchanged in `main()`.
* This is because `a` is a *copy* of `i`, not a reference to it.

**Why it matters:**
This behavior is central to understanding C. You cannot directly modify variables in the caller from inside the callee unless you explicitly pass a pointer (see “pass by reference”—a separate topic).

---

## 4.2 Function Prototypes

**Problem:**
If you call a function before it is defined, the compiler needs to know its signature (return type, argument types).

**Solution:**
A **function prototype** declares the function’s interface ahead of its use.

**Syntax:**
A function prototype is just the first line of the function with a semicolon.

**Example:**

```c
#include <stdio.h>

int foo(void);  // Prototype

int main(void)
{
    int i = foo();
    printf("%d\n", i);  // Output: 3490
}

int foo(void)  // Definition
{
    return 3490;
}
```

**Best Practice:**

* Always declare prototypes for functions defined later, especially those defined in other files.
* Do *not* rely on implicit declarations (allowed in very old C standards, forbidden now).

**Why doesn’t printf() require a prototype in our code?**
Because the prototype is provided by the standard library’s header file `<stdio.h>`, which you include at the top with `#include <stdio.h>`.

---

## 4.3 Empty Parameter Lists

**Modern Best Practice:**

* Always use `void` to indicate a function takes no parameters, both in function definitions and prototypes.

**Example—Correct:**

```c
void foo(void)  // Proper: explicitly declares no parameters
{
    printf("Hello, world!\n");
}
```

**Example—Incorrect (but sometimes seen in old code):**

```c
void foo()  // Ambiguous—should be avoided in new code
{
    printf("Hello, world!\n");
}
```

**Critical difference in prototypes:**

```c
void foo();       // Ambiguous: disables type checking for arguments!
void foo(void);   // Proper: compiler checks that no arguments are passed
```

**Summary:**
Always use `void` for empty parameter lists in modern C code to ensure type safety and avoid legacy ambiguity.

---

## Key Takeaways

* Functions in C require explicit declaration of argument and return types.
* Arguments are always passed by value (copied into local parameters).
* Use prototypes to declare functions before use, especially across multiple files.
* Always use `void` in parameter lists to clearly indicate when no arguments are required.

---
