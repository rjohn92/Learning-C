# To Remember 
---
## What is a Pointer??
A pointer is a variable that stores a memory address. A memory address is the 
the unique number that identifies a specific location in a device's RAM. This is how the CPU, OS and my program refers to and accesses bytes of memory.

So, to me, a memory address is just the street address for a single mailbox (byte) in a city (RAM). So every person has an address (hopefully I guess). And every person's address is unique. 

So we can have:
```c
int x = 23;
```

An int type is always 4 bytes in RAM. Then maybe the OS puts x at address 0x1000. So x is the variable. The address of x is found by this:

```c
int *ptr =&x 
```

This is a pointer to the variable of x. and the 'pointer' variable holds the address of x. And in address format it would look like 0x100. 

Putting it together:
```c
int x = 23;
int *ptr = &x;
```

This doesn't mean the pointer itself is an int. It just means that the variable ptr is a pointer to an int variable. 

---

