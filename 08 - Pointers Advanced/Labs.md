# Module: Advanced Pointers and Memory Management — Labs

---

## Lab 1: Pointer Arithmetic

- Declare an array of `int`.
- Use a pointer to traverse and print all values using pointer arithmetic (not array indexing).
- Print the address of each element using `%p`.

---

## Lab 2: Dynamic Allocation with `malloc`/`calloc`/`realloc`

- Allocate memory for an `int` array with `malloc`. Initialize and print the values.
- Expand the array to twice its size using `realloc`, initialize the new elements, and print all values.
- Repeat the above with `calloc`. Observe and document zero-initialization.

---

## Lab 3: Memory Leaks and Dangling Pointers

- Write a function that allocates memory for a struct, fills it, but forgets to `free` it.
- Use Valgrind (or similar tool) to detect the memory leak.
- Fix the code so all allocated memory is properly freed. Set the pointer to `NULL` after freeing.

---

## Lab 4: Stack vs Heap Observation

- Allocate an `int` array on the stack and another on the heap.
- Print addresses of both arrays. Observe and record which is “higher”/“lower” in memory.
- Try to return a pointer to a stack variable from a function. Observe the warning/error and explain why it’s unsafe.

---

## Lab 5: Debugging Heap Bugs

- Intentionally write code that:
  - Double-frees a pointer.
  - Frees memory, then writes to it (“use after free”).
  - Writes past the end of an allocated array (buffer overflow).
- Run each scenario with Valgrind or GDB. Document the observed errors/messages.

---

## Lab 6: Real-World CNO Exercise — Parsing a CTF Buffer

- Write code that reads a file or input buffer, dynamically allocates space, and parses out integers or strings.
- (Optional) Introduce and then fix a classic bug: off-by-one buffer overflow or improper use of `realloc`.

---
