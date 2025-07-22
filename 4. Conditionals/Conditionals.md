
# Module 4: Conditionals (`if`, `else if`, `else`, `switch`)

Conditionals let your program make decisions: “if this, do that; otherwise, do something else.”  
**Mastering conditionals is foundational for real-world logic, program security, and understanding binary flow.**

---

## What You’ll Learn

- Syntax and semantics of `if`, `else if`, `else`, and `switch` in C
- Boolean (true/false) logic and how conditions work
- The difference between assignment (`=`) and comparison (`==`)
- Compound and nested conditionals, including `switch`
- Common rookie mistakes and pitfalls
- CNO/RE security and reverse engineering context

---

## 1. Basic `if` Statement

Runs a block of code if the condition is true (non-zero):

```c
int score = 75;
if (score >= 60) {
    printf("Passed!\n");
}
```

---

## 2. Adding `else` and `else if`

```c
if (score >= 90) {
    printf("A grade\n");
} else if (score >= 80) {
    printf("B grade\n");
} else if (score >= 70) {
    printf("C grade\n");
} else {
    printf("Below C\n");
}
```

---

## 3. Boolean Logic in C

- Any **nonzero value is true**, zero is false.
- Use logical operators: `&&` (and), `||` (or), `!` (not):

```c
if (x > 0 && x < 10) { ... }
if (!done) { ... }
```

---

## 4. The `switch` Statement

**Use `switch` for checking a variable against several constant integer values.**  
Often cleaner and faster than a long chain of `if...else if`.

```c
int option = 2;
switch (option) {
    case 1:
        printf("Option 1 selected\n");
        break;
    case 2:
        printf("Option 2 selected\n");
        break;
    case 3:
        printf("Option 3 selected\n");
        break;
    default:
        printf("Unknown option\n");
        break;
}
```
- `switch` evaluates the variable/expression and jumps to the matching `case`.
- **Always use `break;`** to prevent “fall through” (running all following cases).
- The `default` block runs if no case matches.

**Common rookie bugs:**
- Forgetting `break;` — causes *fallthrough* (can be useful, but usually accidental and dangerous).
- Cases must be **constant integer values** (no ranges or variables).
- Only one variable/expression can be checked per switch.

**Best practice:**  
Always include a `default` case for safety.

---

## 5. Common Pitfalls & Bugs

- **Assignment vs. Comparison:**  
  `if (x = 5)` assigns 5 to x, always true! Use `if (x == 5)`.
- **Unbraced blocks:** Only the next line after `if` is controlled without `{}`.
- **Dangling else:** Always use braces for clarity.
- **Direct float comparisons:** Avoid `if (x == 0.1)`; use a tolerance check.
- **Switch fallthrough:** Missing `break;` will run multiple cases.

---

## 6. CNO/RE Relevance

- Logic bugs in conditionals (especially assignments, missing breaks, or unchecked defaults) can cause privilege escalation or bypasses.
- `switch` and `if` branches become `jmp`, `jne`, `je`, `jmp table` in assembly—key for reverse engineering.
- Vulnerabilities often hide in “default” or fallthrough paths.

---

## 7. Best Practices

- **Always use braces `{}`** for multi-line blocks—even for one line.
- **Always use `break;`** in each switch case, unless intentional fallthrough (and comment it!).
- **Don’t compare floats directly**; use a tolerance.
- **Be explicit and comment complex logic.**
- **Use `switch` for integer/enum decision trees, not for strings or ranges.**

---

## Practice / Exercises

1. Write a function that prints the name of a weekday (1-7) using `switch`.

2. Expand your earlier “grade calculator” using both `if/else if` and `switch`—compare clarity.

3. Write a menu-driven program using `switch` for options.

4. Remove `break;` from a case in your switch and observe what happens.

5. (RE) Find a C program with a `switch` and examine its jump table in GDB or Ghidra.

---

## Further Reading

- [If Statements in C (Tutorialspoint)](https://www.tutorialspoint.com/cprogramming/c_decision_making.htm)

- [Switch Statement in C (GeeksforGeeks)](https://www.geeksforgeeks.org/switch-statement-in-c/)

- [Boolean Logic in C (Learn-C.org)](https://www.learn-c.org/en/Conditions)

---

**Key Takeaway:**  
*Conditionals and switch logic let you control your program’s flow and are central to security.  
Always use braces, handle all cases (including default), and comment complex decisions!*

---
