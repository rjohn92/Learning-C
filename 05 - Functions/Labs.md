# Early C Functions Labs (No Pointers/Arrays)

**Scope:**  
- Variables and types
- Arithmetic and expressions
- Conditionals and loops
- Function basics (no pointers/arrays)

---

## Lab 1: Your First Function

**Goal:**  
Write a function that takes an integer, adds 10, and returns the result.

**Steps:**
1. Define a function `int add_ten(int n);`
2. In `main()`, declare an integer, assign it a value, call your function, and print the result.

---

## Lab 2: Using Functions With Conditional Logic

**Goal:**  
Write a function that checks if a number is positive or negative.

**Steps:**
1. Define a function `void check_sign(int n);`
2. Inside, use `if`/`else` to print `"Positive"` or `"Negative"` (assume zero is positive).
3. In `main()`, call the function with at least two different values.

---

## Lab 3: Functions With No Arguments

**Goal:**  
Write a function that prints your favorite motivational quote.

**Steps:**
1. Define `void print_quote(void);`
2. Call it from `main()` at the program start.

---

## Lab 4: Functions Returning void

**Goal:**  
Write a function that prints a line of asterisks (*) as a separator.

**Steps:**
1. Define `void print_separator(void);`
2. Call it before and after a printf statement in `main()`.

---

## Lab 5: Pass By Value Demonstration

**Goal:**  
Show that function arguments are passed by value.

**Steps:**
1. Write `void try_to_modify(int n);` which sets `n = 100;` and prints it.
2. In `main()`, declare `int x = 5;`, call your function, then print `x` afterwards.
3. Observe: the value of `x` in `main()` does not change.

---

## Lab 6: Loop + Function Integration

**Goal:**  
Use a function to print numbers from 1 to N (N set in `main()`), demonstrating loops and function calls.

**Steps:**
1. Define `void print_numbers(int n);`
2. Inside, use a `for` loop to print numbers from 1 to `n`.
3. Call it from `main()` with a few values.

---

## Lab 7: Function Prototype Usage

**Goal:**  
Practice declaring and using function prototypes.

**Steps:**
1. At the top, write the prototype: `int square(int);`
2. In `main()`, use `square()` before its definition (place `main()` first).
3. Define `int square(int n) { return n * n; }` after `main()`.

---

# Reflection Prompts (for each lab)

- What is the function’s input, and what is its output (if any)?
- Was any variable’s value changed in `main()` as a result of the function? Why/why not?
- What would happen if you omitted the function prototype?

---

**Instructions:**  
Copy each lab to a `.c` file, compile, and run. After each, answer the reflection prompts in your own notes.
