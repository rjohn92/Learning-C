# Summary of Lessons Learned in Pointers Labs

## Lab 1: Pointer Declaration


### Q1: What does `%p` print?

**A:**  
`%p` prints the memory address of a variable (i.e., a pointer value) in an implementation-defined format, usually hexadecimal.

---

### Q2: Is the address always the same between runs? Why or why not?

**A:**  No. Memory addresses change from run to run due to Address Space Layout Randomization (ASLR) and process isolation in modern operating systems. This prevents hardcoded addresses from being reliable and helps mitigate security vulnerabilities.

---

### Key Takeaways

- Always use `%p` for pointer output—never assume addresses are stable.
- Understanding address volatility is foundational for debugging, exploit mitigation, and secure coding.

---