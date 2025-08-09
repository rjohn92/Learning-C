# More Pointer Labs

**Goal:** Understand pointer traversal and addresses.

* Declare `int arr[10]` and initialize deterministically.
* Use `int *p = arr;` and print **addresses** with `%p` and **values** only via `*(p + i)`.
* Also print `&arr[i]` to confirm `arr + i == &arr[i]`.
* **Checkpoints:**

  * Address spacing equals `sizeof(int)`.
  * Values match expected initialization.

---

## Lab 2 — Dynamic Allocation: `malloc` / Safe `realloc` / `calloc`

**Goal:** Allocate, resize, and reason about initialization.

* Allocate `N` ints with `malloc`; check for `NULL`.
* Initialize and print all elements.
* Use **safe realloc pattern**:

  ```c
  tmp = realloc(p, 2 * N * sizeof *p);
  if (!tmp) { free(p); fail; }
  p = tmp;
  ```
* Initialize the **new tail** `[N, 2N)` and print.
* Repeat the run with `calloc(N, sizeof *p)`:

  * Skip manual init initially.
  * **Document** observed zero-init vs `malloc`’s indeterminate memory.
* **Checkpoints:** Only initial `calloc` region is zero; `realloc` does **not** zero extension.

---

## Lab 3 — Stack vs Heap Observation

**Goal:** Recognize storage duration and address regions.

* Create `int stack_arr[4];` and `int *heap_arr = malloc(4 * sizeof *heap_arr);`
* Print `%p` for both base addresses.
* Note which appears higher/lower **for this run** (ASLR means not guaranteed in all runs).
* Demonstrate why returning stack addresses is unsafe:

  ```c
  int *bad_func(void) {
      int local = 42;
      return &local; // Dangling after return
  }
  ```

  Capture compiler warning in comments.
* **Checkpoint:** Document lifetimes: automatic vs dynamic.

---

## Lab 4 — NULL, Dangling, and Ownership

**Goal:** Recognize and prevent pointer lifetime errors.

* Show `int *p = NULL;` and explain why `*p = 1;` is UB (comment after observing once).
* Show **dangling pointer** by:

  * `free(p); p = NULL;` then explain why using old value is UB.
  * A function that safely uses an out-parameter instead of returning `&local`.
* **Ownership rules doc:**

  * Allocator returns ownership; caller must `free`.
  * After `free`, set pointer to `NULL`.
  * No double-free; no use-after-free.
* **Checkpoint:** Short written rationale for each rule.

---

## Lab 5 — Boundary Discipline

**Goal:** Avoid off-by-one and overflow.

* Allocate `N` ints; write to indices `[0..N-1]`.
* Add guarded writer that rejects `i == N`.
* Add assertions (`assert(i < N)`) to enforce bounds.
* **Checkpoint:** Run with deliberate bad index and see assertion failure (ensure `NDEBUG` is off).

---

## Lab 6 — Slice-Style APIs in C (Pointer + Length)

**Goal:** Work with subarrays without language-level slicing.

* Write `print_n(const int *base, size_t len)`; call with `(arr, 5)` and `(arr + 5, 5)`.
* Write `sum_n(const int *base, size_t len)`; verify against sum of full array.
* **Checkpoint:** Document invariant: pointer = start; length = number of elements.

---

## Notes

* Always `free()` heap allocations at end of lab code.
* Cast pointers to `(void*)` when printing with `%p`.
* For repeatable address observations, run with ASLR disabled (optional; not required for concept).
