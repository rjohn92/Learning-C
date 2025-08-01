# Essential C Pointers Labs

## Lab 1: Address-of and Pointer Declaration

**Goal:**  
Declare an int variable. Print its value and its address.

**Steps:**
1. `int x = 42;`
2. `printf("Value: %d\\n", x);`
3. `printf("Address: %p\\n", (void *)&x);`

**Questions:**
- What does `%p` print?
- Is the address always the same between runs? Why/why not?

---

## Lab 2: Declaring and Assigning a Pointer

**Goal:**  
Declare a pointer-to-int. Assign it the address of an int variable.

**Steps:**
1. `int a = 5;`
2. `int *p = &a;`
3. Print `p` (the pointer’s value) and `*p` (the value it points to).

---

## Lab 3: Modifying via Dereference

**Goal:**  
Show that writing via a pointer changes the original variable.

**Steps:**
1. As above, assign `p = &a;`
2. Set `*p = 100;`
3. Print `a` after the modification. It should now be `100`.

---

## Lab 4: Function that Modifies Value via Pointer

**Goal:**  
Pass a pointer to a function. Have it modify the original variable.

**Steps:**
1. Write `void set_to_zero(int *ptr);`
2. In `main()`, `int n = 77;`
3. Call `set_to_zero(&n);`
4. Print `n` after the call—should be zero.

---

## Lab 5: Pointer Syntax Pitfalls

**Goal:**  
Understand declaration syntax.

**Questions:**
- Given `int *a, b, *c;`, which variables are pointers? Which are plain ints?
- Write a comment after each to clarify.

---

## Lab 6: NULL Pointers

**Goal:**  
Assign a pointer to `NULL` and show that dereferencing it causes a crash (comment out that line after demonstration).

**Steps:**
1. `int *p = NULL;`
2. Attempt `*p = 1;` // Explain why this is undefined behavior.

---

## Lab 7: sizeof With Pointers

**Goal:**  
Compare the size of int, int*, and *p.

**Steps:**
1. `int *p;`
2. Print sizes: `sizeof(int)`, `sizeof(p)`, `sizeof(*p)`.
3. Note that pointer size depends on architecture (typically 4 bytes on 32-bit, 8 on 64-bit).

---

## Reflection Prompts

- What happens if you print a pointer before initializing it?
- Why do pointers enable changing variables outside the function scope?
- Why is pointer type (`int*` vs `float*`) critical?
- What happens if you dereference a NULL or uninitialized pointer?

---

**If you want answers or sample code, ask for any lab.**

---

**Summary for CNO Prep:**  
- **Mastery of pointers (and memory) is *table stakes* for CNO work.**  
- If you cannot fluently use and explain pointers, you will struggle with 80%+ of CNO, RE, and exploit dev tasks.
- These labs are an *absolute baseline*—review, drill, and make sure you can modify them for new scenarios.

---

**Let me know if you want this in a downloadable Markdown file, want next steps (arrays, pointer arithmetic, struct pointers), or need sample code for any step.**
