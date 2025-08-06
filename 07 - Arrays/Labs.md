# C Array Labs: Foundations and Best Practices

---

## Overview

This lab set is designed to build foundational skill in C array handling for systems programming, security, and professional development. Each lab is practical, grounded, and explained with real-world relevance. Concepts covered: variables, pointers, conditionals, loops, functions.

---

## Lab 1: Array Declaration and Indexing

**Objective:**
Understand how to declare, initialize, and access arrays. Observe that indexing starts at zero and that elements are stored contiguously.

**Steps:**

1. Declare an array of 5 integers.
2. Assign values `10, 20, 30, 40, 50` to each element using direct assignment (not a loop).
3. Print each element and its address.
4. Add a comment showing how the addresses are spaced.

**Questions:**

* What do you notice about the addresses?
* What happens if you try to print `a[5]`?

---

## Lab 2: Array Initialization and the `sizeof` Trick

**Objective:**
Use `sizeof` to determine the length of an array. Understand why this works only in the declaring scope.

**Steps:**

1. Declare and initialize an array of 8 `char`s with some ASCII characters.
2. Use `sizeof` to print:

   * The size of the array in bytes
   * The size of one element
   * The number of elements in the array
3. Pass the array to a function and repeat the measurements there.

**Questions:**

* What results do you get in `main` vs. inside the function? Why?

---

## Lab 3: Array Input and Summation

**Objective:**
Use a loop to populate an array, then sum its values. Reinforce use of loops, conditionals, and arrays together.

**Steps:**

1. Declare an array of 6 integers.
2. Use a `for` loop to prompt the user to enter 6 numbers (use `scanf`).
3. Store each number in the array.
4. After the loop, sum all values using another loop and print the result.

**Extension:**
Print the maximum and minimum values in the array.

---

## Lab 4: Functions that Modify Arrays

**Objective:**
Pass an array to a function and modify its contents. Demonstrate “pass by reference” for arrays.

**Steps:**

1. Write a function `void double_values(int *arr, int len)` that doubles each element of the array.
2. In `main`, declare and initialize an array of 5 integers.
3. Print the original array.
4. Call `double_values` with the array and its length.
5. Print the modified array.

**Questions:**

* Why do changes inside the function persist in `main`?
* What would happen if you tried to return the array instead?

---

## Lab 5: Array and Pointer Equivalence

**Objective:**
Show the equivalence of array indexing and pointer arithmetic.

**Steps:**

1. Declare and initialize an array of 4 integers.
2. Use both array notation (`a[i]`) and pointer notation (`*(a + i)`) to print all elements.
3. Add a comment explaining how the memory addresses relate.

**Questions:**

* What does `a[i]` mean under the hood?
* Why is this equivalence important for understanding memory layout and pointer bugs?

---

## Lab 6: Out-of-Bounds Access (Undefined Behavior Demo)

**Objective:**
Demonstrate what happens when you read or write past the end of an array.
**Warning: This is intentionally unsafe and should only be used for controlled demonstration.**

**Steps:**

1. Declare an array of 5 integers and initialize with known values.
2. Print all 5 values, then attempt to print `a[5]`, `a[6]`.
3. Try writing to `a[7] = 12345` and see if you can observe an effect.
4. Run the program multiple times.

**Questions:**

* What values do you see when accessing out-of-bounds elements?
* What risks does this behavior create in real-world C or security-sensitive code?

---

## Lab 7: Passing Array Segments to Functions

**Objective:**
Use pointers to pass a “slice” of an array to a function. Reinforce how pointers and arrays interact.

**Steps:**

1. Declare an array of 10 integers (initialize as you like).
2. Write a function that prints N elements from a given starting pointer.
3. In `main`, call the function to print elements 0–4, then elements 5–9.

**Questions:**

* How does pointer arithmetic let you “slice” an array?
* Why does this technique matter for buffer processing or CNO work?

---
