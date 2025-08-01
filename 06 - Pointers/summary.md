# Summary of Lessons Learned in Pointers Labs

## Lab 1: Pointer Declaration


### Q1: What does `%p` print?

**A:**  `%p` prints the memory address of a variable (i.e., a pointer value) in an implementation-defined format, usually hexadecimal.



### Q2: Is the address always the same between runs? Why or why not?

**A:**  No. Memory addresses change from run to run due to Address Space Layout Randomization (ASLR) and process isolation in modern operating systems. This prevents hardcoded addresses from being reliable and helps mitigate security vulnerabilities.


### Key Takeaways

- Always use `%p` for pointer output—never assume addresses are stable.
- Understanding address volatility is foundational for debugging, exploit mitigation, and secure coding.

---

# Summary: Pointers Lab: Basic Pointer Declaration, Addressing, and Dereferencing

## Key Concepts Learned

### 1. Variable Declaration and Initialization
- `int a = 5;`  
  Declares an integer variable `a` and sets its value to 5.

### 2. Referencing (Getting the Address)
- The `&` operator is used to get the address of a variable.  
  Example: `&a` returns the memory address of `a`.

### 3. Pointer Declaration and Assignment
- `int *p = &a;`  
  Declares a pointer to `int` (`p`) and initializes it with the address of `a`.
- `p` now “points to” `a`; it stores the address of `a`.

### 4. Dereferencing (Accessing the Value)
- The `*` operator is used to access the value stored at the address held by a pointer.
  - Example: `*p` gives the value of `a` (in this case, `5`).

### 5. Printing Addresses and Values
- To print an address, use `%p` and cast the address to `void *` for standards compliance:  
  `printf("%p\n", (void*)&a);` or `printf("%p\n", (void*)p);`
- To print a value via a pointer, use `%d` and dereference the pointer:  
  `printf("%d\n", *p);`

### 6. Pointer Assignment and Value Change
- Assigning `*p = 10;` updates the value of `a` through the pointer.  
  Both `a` and `*p` will be `10` afterward.

---

## Practical Use Cases

- **Referencing** is essential for passing variables by reference to functions, manipulating data structures, and interfacing with hardware/memory directly.
- **Dereferencing** lets you access or modify the value stored at a memory location. That's a fundamental skill for any C programmer, and critical for systems and CNO work.

---

## Example Code Snippet

```c
int a = 5;
int *p = &a;

printf("Value of a: %d\n", a);                  // prints 5
printf("Address of a: %p\n", (void*)&a);        // prints address of a
printf("Pointer p holds address: %p\n", (void*)p); // should match address of a
printf("Value pointed to by p (*p): %d\n", *p); // prints 5

*p = 10;
printf("Value of a after *p = 10: %d\n", a);    // prints 10
```