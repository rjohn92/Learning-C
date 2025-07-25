# Bitwise Operators in C: A Beginner’s Deep Dive

---

## 🧠 What Are Bits?

* A **bit** is a binary digit: 0 or 1.
* Computers store numbers in memory as sequences of bits.
  For example: `unsigned char x = 12;`
  In binary, 12 is `00001100` (that’s 8 bits = 1 byte).

---

## 🔨 What Are Bitwise Operators?

Bitwise operators let you **directly manipulate individual bits** of a number.
They operate on the *binary* representation, not the decimal value.

---

## The Basic Bitwise Operators

| Operator    | Symbol | What It Does           | Example                 |     |     |
| ----------- | ------ | ---------------------- | ----------------------- | --- | --- |
| AND         | `&`    | Bit is 1 if BOTH are 1 | `a & b`                 |     |     |
| OR          | \`     | \`                     | Bit is 1 if EITHER is 1 | \`a | b\` |
| XOR         | `^`    | Bit is 1 if DIFFERENT  | `a ^ b`                 |     |     |
| NOT         | `~`    | Flips all bits         | `~a`                    |     |     |
| LEFT SHIFT  | `<<`   | Moves bits left        | `a << n`                |     |     |
| RIGHT SHIFT | `>>`   | Moves bits right       | `a >> n`                |     |     |

---

## 📝 Examples (Visual)

Let’s use:
`unsigned char a = 12;`  // 00001100
`unsigned char b = 10;`  // 00001010

### AND (`&`):

```
   00001100  (12)
 & 00001010  (10)
 = 00001000  (8)
```

So, `12 & 10 == 8`

---

### OR (`|`):

```
   00001100
 | 00001010
 = 00001110  (14)
```

So, `12 | 10 == 14`

---

### XOR (`^`):

```
   00001100
 ^ 00001010
 = 00000110  (6)
```

So, `12 ^ 10 == 6`

---

### NOT (`~`):

* Flips every bit (for `unsigned char a = 12`):

```
  00001100 (12)
~ 11110011 (243)   // On 8 bits; with `int`, the result includes sign bits!
```

So, `~12 == 243` (for `unsigned char`), but with `int`, you’ll get a negative number.

---

### SHIFT (`<<`, `>>`):

* Shifting bits to the left/right is like multiplying/dividing by 2.

```c
unsigned char a = 3; // 00000011
a << 1; // 00000110 = 6
a >> 1; // 00000001 = 1
```

---

## 🕵️‍♂️ Why Do Bitwise Operators Matter?

* **Low-level programming:** Setting/checking “flags” (one bit per feature).
* **Security/CNO:** Exploits, protocols, crypto, and malware analysis use bitwise tricks constantly.
* **Performance:** Fastest way to manipulate data at the binary level.

---

## 🛑 Common Bitwise Pitfalls

* **Confusing `&` (bitwise AND) with `&&` (logical AND)** — they are NOT the same!
* **Bitwise NOT with signed types:** `~` on an `int` can produce negative results (because of two’s complement representation).
* **Shifting by too much:** Shifting a value by more bits than its size (e.g., `x << 32` on a 32-bit int) is undefined.

---

## 🧩 Real-World Use Example: Checking for Even/Odd

Check if a number is even:

```c
if ((x & 1) == 0) // The last bit is 0: number is even
```

Check if a number is odd:

```c
if (x & 1) // The last bit is 1: number is odd
```

---

## 🧪 Lab for Practice

1. Set two unsigned char variables to 12 and 10.
2. Print their binary forms (by hand, or use a table).
3. Compute and print:

   * `a & b`
   * `a | b`
   * `a ^ b`
   * `~a`
   * `a << 1`
   * `a >> 1`
4. For each, write down the binary and decimal result.

---

## 💡 Summary

* **Bitwise ops manipulate data at the level of 1s and 0s.**
* They’re essential for CNO, embedded, security, and RE.
* Understand the difference between bitwise (`&`, `|`, etc.) and logical (`&&`, `||`, etc.) operators.
