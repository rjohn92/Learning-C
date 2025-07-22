# Module 3: Operators and Expressions

Welcome to the Operators and Expressions module. In C, operators are the building blocks of almost every calculation, condition, and logic check in your code.  
Understanding how they work—and where they can bite you—is essential for writing correct and secure programs.

---

## What You'll Learn

- Types of operators in C: arithmetic, comparison, logical, and bitwise
- How expressions are built from variables, literals, and operators
- Operator precedence and associativity: who “goes first” in a complex line
- Compound assignment and increment/decrement shortcuts
- Classic C gotchas (integer promotion, unexpected results, overflow)

---

## 1. Arithmetic Operators

- Addition `+`, subtraction `-`, multiplication `*`, division `/`, modulus `%`
- Example:
    ```c
    int a = 10, b = 3;
    int sum = a + b;      // 13
    int prod = a * b;     // 30
    int quot = a / b;     // 3  (integer division!)
    int rem = a % b;      // 1  (remainder)
    ```

---

## 2. Comparison Operators

- Equal `==`, not equal `!=`, greater/less `<`, `>`, `<=`, `>=`
- Used in conditions (`if`, `while`, etc.)
    ```c
    if (a == b) { ... }
    if (a >= 5) { ... }
    ```

---

## 3. Logical Operators

- AND `&&`, OR `||`, NOT `!`
- Used for combining/complementing conditions
    ```c
    if (a > 0 && b > 0) { ... }
    if (!(a == b)) { ... }
    ```

---

## 4. Bitwise Operators

- AND `&`, OR `|`, XOR `^`, NOT `~`, shift left `<<`, shift right `>>`
- Work at the *bit* level—used heavily in low-level, CNO, and embedded work
    ```c
    unsigned char flags = 0b10101010;
    unsigned char mask = 0b00001111;
    unsigned char result = flags & mask; // 0b00001010
    ```

---

## 5. Compound Assignment and Increment/Decrement

- Shortcuts: `+=`, `-=`, `*=`, `/=`, `%=`  
    ```c
    x += 3; // same as x = x + 3;
    ```
- `++` (increment), `--` (decrement)  
    ```c
    x++; // adds 1 to x
    y--; // subtracts 1 from y
    ```

---

## 6. Precedence and Associativity

- Some operators are “stronger” and are evaluated first (e.g., `*` before `+`)
- Parentheses can (and should) be used for clarity
    ```c
    int x = 2 + 3 * 4;   // x == 14, not 20!
    int y = (2 + 3) * 4; // y == 20
    ```
- **Associativity**: When operators have the same precedence, which way does C evaluate? (Usually left-to-right, but not always)

---

## 7. Classic C “Gotchas” (Common Bugs)

- **Integer division:** `5 / 2` gives `2`, not `2.5`. Watch for truncation!
- **Mixing signed and unsigned:** Can cause surprising results or bugs
- **Assignment `=` vs equality `==`:** `if (x = 5)` assigns, doesn’t compare!
- **Operator precedence mistakes:** Always use parentheses to make intent clear
- **Integer overflow:** Adding large numbers can wrap around to negatives (or zero)

---

## CNO/RE Relevance

- Bitwise and shift operators are fundamental for low-level protocols, parsing, and exploit development.
- Many vulnerabilities stem from assumptions about operator order or integer promotion/overflow.
- Reading assembly or reverse engineering? Recognizing operator patterns helps you map C source to disassembly.

---

## Practice / Exercises

- Write a calculator that performs all basic arithmetic operations.
- Experiment with logical and bitwise operators—print out results for various combinations.
- Write expressions mixing multiple operators and use parentheses to predict and check results.
- Trigger and investigate integer division and overflow cases.
- Try using increment/decrement inside a loop or an expression—see what changes!

---

## Further Reading

- [C Operators and Expressions (Tutorialspoint)](https://www.tutorialspoint.com/cprogramming/c_operators.htm)
- [C Operator Precedence (GeeksforGeeks)](https://www.geeksforgeeks.org/operator-precedence-and-associativity-in-c/)
- [Bitwise Operators in C (GeeksforGeeks)](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)

---

**Key Takeaway:**  
Mastering operators and expressions is the key to unlocking powerful, concise, and bug-free C code. Always be clear about what your code is doing—don’t be afraid to use parentheses for readability and correctness!

---
