# Stack vs Heap — A Practical, Low‑Level Guide

> Goal: give you a production‑grade mental model that explains **what** each region is, **how** it’s laid out, **why** it exists, **how** the syntax maps to machine behavior, and **when** to use each — with concrete examples and failure modes.

---

## 0) TL;DR decision rules

* **Use the stack** for: small, short‑lived data local to a function; fixed‑size arrays; scratch temporaries; recursion state.
* **Use the heap** for: large data, runtime‑determined sizes, objects that must outlive a function, or be shared across modules/threads.
* If you can express it safely on the stack, prefer stack → faster, simpler, fewer failure modes.

---

## 1) Process memory map (virtual address space)

A typical 64‑bit Linux process (simplified):

```
Low addresses                                                High addresses
+----------------------+  .text  (code, read‑only)
|  instructions        |
+----------------------+  .rodata (string literals, const)
|  read‑only data      |
+----------------------+  .data/.bss (globals/statics)
|  global variables    |
+----------------------+  HEAP  (managed by allocator)  ↑ grows upward
|      ...             |
|  mmap regions        |
|      ...             |
+----------------------+  STACK (per thread)            ↓ grows downward
```

Notes:

* **ASLR** randomizes base addresses. Growth “up” vs “down” is a convention: heap requests larger addresses, stack uses lower addresses by decrementing its pointer. LIFO order is independent of numeric direction.
* Each **thread** has its **own stack**. The heap is **shared** by all threads in the process.

---

## 2) The Stack (automatic storage)

### What it is

A LIFO region maintaining **call frames**. Each function call pushes a frame holding:

* return address
* saved frame/base pointer (ABI‑dependent)
* callee‑saved registers (if any)
* local variables / spills

### Why it “grows downward”

“Downward” means “toward smaller addresses.” On entry, the prologue **subtracts** from the stack pointer to reserve space; on exit, the epilogue **adds** it back. This choice lets the heap grow from the opposite side so they can “meet in the middle,” maximizing usable space.

### ABI‑level view (x86‑64 SysV example)

```
push   %rbp             ; save caller’s frame pointer
mov    %rsp, %rbp       ; establish callee frame
sub    $0x30, %rsp      ; reserve 48 bytes for locals (aligned)
...
leave                   ; mov %rbp,%rsp ; pop %rbp
ret
```

Local `int x;` is accessed via a fixed negative offset from `%rbp` or `%rsp`.

### Syntax mapping (C)

```c
void f(void) {
    int x = 42;        // stack local
    int arr[64];       // stack array (lifetime = this call)
}                      // frame is popped here; x/arr cease to exist
```

No `free` is needed; lifetime is tied to scope.

### Strengths

* **Speed**: pointer adjust + fixed offsets → extremely fast.
* **Simplicity**: ownership is trivial; fewer failure modes.

### Constraints

* **Bounded size** (commonly a few MB per thread). Large objects risk **stack overflow**.
* **Lifetime**: invalid once the function returns. Returning `&x` is a **dangling pointer**.

### Observability

* In `gdb`: `bt` (backtrace), `info frame`, `p &x`.

---

## 3) The Heap (dynamic storage)

### What it is

A process‑wide pool managed by an **allocator** (`malloc/calloc/realloc/free`). Under the hood, the allocator keeps metadata (size, free lists, tcache, bins) and obtains pages from the OS (e.g., `mmap`/`sbrk`).

### Syntax mapping (C)

```c
int *a = malloc(100 * sizeof *a);   // uninitialized bytes
int *b = calloc(100, sizeof *b);    // zero‑initialized
b = realloc(b, 200 * sizeof *b);    // may move; old ptr invalid if moved
free(a);                             // you must release
free(b);
```

### Strengths

* **Flexible size** at runtime.
* **Flexible lifetime**: survives beyond a single scope; can be shared.
* **Large capacity** compared to stack.

### Costs / risks

* **Overhead**: allocation bookkeeping, potential locks → slower.
* **Correctness hazards**: leaks, double‑free, use‑after‑free, overflow into metadata.
* **Fragmentation**: many differently sized alloc/free cycles leave holes.

### Ownership rule of thumb

* The function that **allocates** usually defines who **owns** and must **free** (document this). Ambiguity causes leaks.

---

## 4) Arrays vs pointers, and “array decay”

```c
void g(void) {
    int s[4];           // array object on the STACK
    int *p = s;         // "decays" to pointer to first element (type: int*)
    size_t n = sizeof s;    // == 16 (size of the whole array)
    size_t m = sizeof p;    // == 8  (size of a pointer on x86‑64)
}
```

* An **array** is a contiguous block with fixed size known at compile time (if not VLA).
* In most expressions, array **decays** to pointer to its first element (`&s[0]`). That is why `sizeof` differs.
* Heap arrays are just blocks you manually created; indexing and pointer arithmetic work the same on the resulting pointer.

---

## 5) When to choose which (with rationale)

| Requirement                           | Prefer | Why                                                                 |
| ------------------------------------- | ------ | ------------------------------------------------------------------- |
| Small, fixed size, local scratch      | Stack  | Faster, zero bookkeeping, scope‑bound lifetime.                     |
| Large buffers (MB/GB)                 | Heap   | Avoids stack overflow; allocator can back with pages on demand.     |
| Size known only at runtime            | Heap   | Flexibility; stack VLAs exist (C99) but are non‑portable and risky. |
| Data must outlive current function    | Heap   | Stack dies on return.                                               |
| Shared across threads/modules         | Heap   | Stack is per‑thread; heap is process‑wide.                          |
| Hot loops with tiny, short‑lived objs | Stack  | Avoid allocator overhead; reuse stack space each iteration.         |

---

## 6) Correctness hazards and how to see them

* **Dangling stack pointer**:

  ```c
  int *f(void){ int x=7; return &x; } // UB: x gone after return
  ```
* **Leak**: allocate without a corresponding `free` on all paths (handle early returns, errors).
* **Double free**: calling `free(ptr)` twice on same pointer → allocator corruption.
* **Use‑after‑free**: keep a stale pointer and dereference later.
* **Off‑by‑one / overflow**: write past the end; on heap can smash metadata; on stack can clobber return address (mitigations: NX, canaries, ASLR — but bugs still exploitable in some contexts).

**Tooling**: build with `-fsanitize=address,undefined`, use `valgrind`/`memcheck`, `clang‑tidy`, static analyzers. These catch the majority of lifetime/ bounds issues early.

---

## 7) Concrete examples (stack vs heap)

### A) Safe stack usage

```c
void sum4(void) {
    int a[4] = {1,2,3,4};
    int s = 0;                 // locals on stack
    for (int i=0;i<4;i++) s += a[i];
}                              // frame popped here
```

### B) Returning data (requires heap)

```c
int *make_range(size_t n) {
    int *a = malloc(n * sizeof *a);
    if (!a) return NULL;
    for (size_t i=0;i<n;i++) a[i] = (int)i;
    return a;                  // OK: survives caller’s scope
}

void use(void) {
    size_t n = 1000;
    int *a = make_range(n);
    if (!a) return;
    /* ... use a ... */
    free(a);                   // caller owns and frees
}
```

### C) Large buffer → heap, not stack

```c
void bad(void){ char big[50<<20]; }  // ~50MB on stack → likely overflow
```

Correct approach:

```c
void ok(void){ char *big = malloc(50u<<20); /* ... */ free(big); }
```

---

## 8) What actually happens on allocation

### Stack

* Prologue subtracts N from stack pointer (e.g., `%rsp -= N`).
* Locals addressed via fixed offsets. No kernel call required; it’s arithmetic on a register.

### Heap

* `malloc(sz)` → allocator finds/creates a suitable chunk; may request pages from OS via `mmap`/`sbrk` (kernel boundary).
* Returns an **aligned** pointer to user region; metadata stored adjacent or out‑of‑line (allocator‑specific).
* `free(ptr)` marks the chunk free; may coalesce with neighbors; may return pages to OS.

This is why stack is orders of magnitude cheaper per allocation.

---

## 9) Philosophy: simplicity first, escape hatch second

* Prefer **deterministic lifetimes** and **local reasoning** → stack.
* Escape to heap **only** when lifetimes/sizes force you to.
* When using heap, enforce **ownership discipline** (document who frees; consider an API surface that makes ownership explicit).

---

## 10) Security & RE tie‑ins (why CNO cares)

* **Stack bugs**: classic ROP chains; mitigations include stack canaries, NX, PIE, ASLR; still relevant in embedded/weakly hardened targets.
* **Heap bugs**: tcache/bin poisoning, UAF, partial overwrites; allocator internals matter in exploitation.
* **RE**: In disassemblers (Ghidra/IDA), stack locals appear at negative offsets from frame pointer; heap pointers appear as values passed to `malloc`/`free`/`new` and stored in globals/structs.

---

## 11) Practical drills (verify the model)

1. **Print addresses**

```c
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int s[4] = {1,2,3,4};
    int *h = malloc(4*sizeof *h);
    printf("stack s: %p\n", (void*)s);
    printf("heap  h: %p\n", (void*)h);
    free(h);
}
```

Observe: addresses likely far apart; heap often at higher addrs; stack at lower.

2. **Dangling pointer demo** (expect ASan to flag)

```c
int *bad(void){ int x=7; return &x; }
```

Compile with `-fsanitize=address` and call it → sanitizer reports use‑after‑scope.

3. **Bounds discipline**
   Add `assert(i < N)` before every write; run with an intentionally bad index → immediate, actionable failure.

---

## 12) Checklist before choosing heap

* Size > \~100KB or data must persist after return?
* Size unknown until runtime?
* Needs sharing across threads/modules?
* Allocation frequency low relative to work done? (Avoid per‑element malloc in hot loops.)
* Do you have a clear owner to `free()` on every path (success, error, early return)?

If any “yes,” heap is justified; otherwise prefer stack.

---

## 13) Glossary

* **ASLR**: Address Space Layout Randomization.
* **ABI**: Application Binary Interface (calling convention, register saves, stack layout rules).
* **Frame**: The portion of the stack dedicated to one active function call.
* **VLA**: Variable Length Array (C99); stack‑allocated, runtime size — non‑portable; use with caution.
* **UAF**: Use After Free.
* **Dangling pointer**: Pointer to memory that is no longer valid.

---

## 14) Quick patterns (API design)

* **Factory returns heap**:

  * `T *make_T(...);` → caller frees.
* **Caller‑provided buffer**:

  * `int fill_buf(char *buf, size_t cap);` → no heap; clear ownership.
* **Out‑param with allocator**:

  * `int make_T(T **out);` → returns 0 on success; caller frees `*out`.

Keep APIs explicit about allocation and ownership to avoid ambiguity.

