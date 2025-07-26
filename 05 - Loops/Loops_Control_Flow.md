
# Module 4: Loops and Control Flow

Loops are how you tell a computer to repeat an action, and control flow structures let you decide which blocks of code run, and when.  
**Mastering loops is critical for writing real software, analyzing exploits, and understanding how programs “move” in memory.**

---

## What You’ll Learn

- The three main types of loops in C (`for`, `while`, `do...while`)
- When to use each type, and how they work internally
- Loop control keywords: `break`, `continue`, and (caution) `goto`
- Common rookie mistakes and bugs
- How loops appear in compiled code and in reverse engineering
- Best practices for safe, readable, and robust loop code

---

## 1. The `for` Loop

Best for: Repeating a fixed number of times, or when you know your loop bounds.

```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```
Structure: for (initialization; condition; increment)

When it stops: When condition is false

---

## 2. The while Loop

Best for: Repeating until a condition changes (not always a known number of times).

```c
int n = 5;
while (n > 0) {
    printf("%d\n", n);
    n--;
}
```
Structure: while (condition)

When it stops: When condition becomes false

---

## 3. The do...while Loop

Best for: When you need to execute the body at least once, no matter what.

```c
int input;
do {
    printf("Enter a number (0 to quit): ");
    scanf("%d", &input);
} while (input != 0);
```
Difference: The body always runs before the condition is checked.

---

## 4. Loop Control: break, continue, goto

- `break` – exits the nearest enclosing loop immediately

```c
for (int i = 0; i < 10; i++) {
    if (i == 5) break;
    printf("%d\n", i);
}
// prints 0 1 2 3 4
```

- `continue` – skips to the next iteration of the loop

```c
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) continue;
    printf("%d\n", i);
}
// prints only odd numbers
```

- `goto` – jumps to a label anywhere in the function  
  Rarely used, dangerous for readability and security; only use for breaking out of deeply nested loops or error handling.

---

## 5. Common Pitfalls & Bugs

- **Infinite loops:** Forgetting to update the loop variable or having a condition that’s never false

```c
while (1) { ... } // Infinite unless you break inside
```

- **Off-by-one errors:** Mixing up < vs <= or starting at 0 vs 1

- **Loop variable scope:** Declaring variables inside the loop can limit access outside it

- **Changing array size or bounds inside the loop:** May lead to crashes or out-of-bounds access

- **Unsafe input in loops:** Especially with scanf/gets, leading to buffer overflows

---

## 6. CNO/Reverse Engineering Relevance

- Loops drive most input parsing and data processing code. Buffer overflows often occur in poorly guarded loops.

- Loop structure appears as “jump” or “conditional branch” in disassembly. Recognizing loop patterns is key in Ghidra/GDB.

- Breaking out of loops with break or goto is visible as jumps/gotos in assembly—critical for analyzing control flow.

---

## 7. Advanced Tips & Best Practices

- Always initialize your loop variables.

- Prefer for for counted loops, while for event-based repetition.

- Never use goto unless absolutely necessary (and comment it heavily).

- Watch for integer overflow in loop counters (rare but dangerous in low-level code).

- Keep loop bodies simple; break out complex logic into functions for readability and safety.

---

## Practice / Exercises

1. Write a loop to print the first 20 even numbers.

2. Sum all elements in an array using a loop.

3. Prompt the user for numbers until they enter zero; then print the total sum.

4. Use a loop to reverse a string in-place.

5. Try creating an infinite loop, then fix it by adding a break.

6. (Advanced) Given an array of bytes, use a loop and bitwise ops to count how many bits are set to 1.

---

## Further Reading

- [Loops in C (Tutorialspoint)](https://www.tutorialspoint.com/cprogramming/c_loops.htm)

- [C Loops and Iteration (GeeksforGeeks)](https://www.geeksforgeeks.org/loops-in-c-and-cpp/)

- [Control Flow in C (Learn-C.org)](https://www.learn-c.org/en/Control_flow)

---

**Key Takeaway:**  
*Loops are the heart of most real C programs and a primary source of logic errors and vulnerabilities.  
Understand them deeply, read your conditions carefully, and always test edge cases!*

---
