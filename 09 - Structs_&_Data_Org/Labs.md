# Module 9 — Structs: Hands‑On Labs

> Build comfort with `struct` fundamentals, `.` vs `->`, arrays of structs, copying, equality, nesting, alignment, and a small dynamic container. Each lab is short and incremental.
>
> **Compile template:**
>
> ```bash
> gcc -std=c11 -Wall -Wextra -Wpedantic -O0 -g -fsanitize=address,undefined labN.c -o labN
> ```

---

## Lab 9.1 — Declare, Initialize, Print

**Goal:** Create a `struct`, write to fields via `.`, and print.

**Starter (lab1.c):**

```c
#include <stdio.h>

struct car {
    char *name;
    float price;   // USD
    int   speed;   // km/h
};

int main(void) {
    struct car saturn;           // uninitialized
    // TODO: set fields via dot
    // saturn.name = ...
    // saturn.price = ...
    // saturn.speed = ...

    // TODO: printf each field on its own line with labels
    return 0;
}
```

**Tasks:**

1. Set `name="Saturn SL/2"`, `price=15999.99f`, `speed=175`.
2. Print with labels.
3. Add `struct car copy = saturn;` then print to confirm a field‑wise copy.

**Checkpoint:** You see two identical cars printed.

**Stretch:** Change only `copy.price`; verify `saturn` didn’t change (copies are independent).

---

## Lab 9.2 — Designated Initializers & Defaults

**Goal:** Use initializer lists—positional and designated.

**Starter (lab2.c):**

```c
#include <stdio.h>

struct car {
    char *name;
    float price;
    int   speed;
};

int main(void) {
    struct car a = {"Saturn SL/2", 16000.99f, 175};    // positional
    struct car b = {.speed=180, .name="Civic"};        // designated; price default‑inits

    // TODO: print both; show b.price default
    return 0;
}
```

**Tasks:**

1. Print both cars; observe `b.price` defaults to `0.0f`.
2. Add a third car with only `.name` set. Print defaults for other fields.

**Checkpoint:** Missing fields default to zero (`0.0f`, `0`).

**Stretch:** Reorder fields in `struct car` to `(int speed, float price, char *name)` and recompile. Did your *designated* initializers still work? (They should.)

---

## Lab 9.3 — Pass by Value vs Pointer (`.` vs `->`)

**Goal:** Write functions that **do** and **don’t** mutate the caller’s struct.

**Starter (lab3.c):**

```c
#include <stdio.h>

struct car { char *name; float price; int speed; };

void discount_by_value(struct car c, float pct) {
    c.price *= (1.0f - pct); // modifies the copy only
}

void discount_by_ptr(struct car *c, float pct) {
    // TODO: use -> to modify the caller's car
}

int main(void) {
    struct car saturn = {.name="Saturn SL/2", .price=16000.0f, .speed=175};
    discount_by_value(saturn, 0.10f);
    printf("After by‑value:   %f\n", saturn.price); // expect unchanged

    discount_by_ptr(&saturn, 0.10f);
    printf("After by‑pointer: %f\n", saturn.price); // expect changed
}
```

**Tasks:** Implement `discount_by_ptr`.

**Checkpoint:** First print unchanged, second reduced by 10%.

**Stretch:** Add `set_speed(struct car *c, int new_speed)` and call it.

---

## Lab 9.4 — Arrays of Structs + Aggregates

**Goal:** Create an array of cars, compute summary stats.

**Starter (lab4.c):**

```c
#include <stdio.h>

struct car { char *name; float price; int speed; };

int main(void) {
    struct car inventory[] = {
        {"Saturn SL/2", 16000.0f, 175},
        {"Civic",       22000.0f, 190},
        {"Miata",       28000.0f, 205},
        {"Corolla",     21000.0f, 185},
    };
    size_t n = sizeof inventory / sizeof inventory[0];

    // TODO: print fastest car's name and speed
    // TODO: compute average price (float)
    return 0;
}
```

**Tasks:**

1. Loop to find max `speed` and print that car.
2. Sum prices and compute average.

**Checkpoint:** You see the fastest model and average price.

**Stretch:** Implement `void print_over_speed(const struct car *a, size_t n, int min_speed)`.

---

## Lab 9.5 — Sorting an Array of Structs

**Goal:** Sort cars by `price` ascending, then by `speed` descending.

**Starter (lab5.c):**

```c
#include <stdio.h>
#include <stdlib.h>

struct car { char *name; float price; int speed; };

int cmp_price_asc(const void *p, const void *q) {
    const struct car *a = p, *b = q;
    return (a->price > b->price) - (a->price < b->price);
}

int cmp_speed_desc(const void *p, const void *q) {
    // TODO: return negative if a should come before b (higher speed first)
}

static void print_all(const struct car *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%-10s $%7.2f %3d km/h\n", a[i].name, a[i].price, a[i].speed);
}

int main(void) {
    struct car inv[] = {
        {"Saturn",16000,175},{"Civic",22000,190},
        {"Miata",28000,205},{"Corolla",21000,185}
    };
    size_t n = sizeof inv/sizeof inv[0];

    qsort(inv, n, sizeof inv[0], cmp_price_asc);
    puts("By price asc:"); print_all(inv, n);

    qsort(inv, n, sizeof inv[0], cmp_speed_desc);
    puts("\nBy speed desc:"); print_all(inv, n);
}
```

**Tasks:** Implement `cmp_speed_desc`.

**Checkpoint:** Output lists sorted as specified.

**Stretch:** After sorting by price, use `bsearch` to find a car with exact `price`.

---

## Lab 9.6 — Dynamic Allocation & Deep Copy

**Goal:** Allocate a `struct` on the heap and implement deep copy of pointer fields.

**Starter (lab6.c):**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car { char *name; float price; int speed; };

struct car *new_car(const char *name, float price, int speed) {
    // TODO: malloc struct car
    // TODO: allocate and copy name (malloc + strcpy)
    // TODO: set fields; return pointer (or NULL on failure)
}

void free_car(struct car *c) {
    // TODO: free name first, then struct
}

struct car deep_copy(const struct car *src) {
    // TODO: return a by‑value copy with a NEW heap‑allocated name
}

int main(void) {
    struct car *a = new_car("Miata", 28000.0f, 205);
    struct car  b = deep_copy(a);

    b.name[0] = 'Y'; // mutate the copy's name

    printf("a.name=%s\n", a->name);
    printf("b.name=%s\n", b.name);

    free_car(a);
    free(b.name); // deep_copy allocated it
}
```

**Tasks:** Implement `new_car`, `free_car`, `deep_copy`.

**Checkpoint:** Changing `b.name` doesn’t change `a->name` → deep copy success.

**Stretch:** Add `struct car shallow_copy(struct car src)` (by‑value copy) and demonstrate the aliasing bug when editing `name`.

---

## Lab 9.7 — Nested Structs & `->` Chaining

**Goal:** Compose structs inside structs.

**Starter (lab7.c):**

```c
#include <stdio.h>

struct engine { int hp; float liters; };
struct car    { char *name; float price; int speed; struct engine eng; };

void tune(struct car *c, int add_hp) {
    // TODO: increase c->eng.hp by add_hp
    // TODO: bump c->speed by (add_hp/10)
}

const struct engine *get_engine_const(const struct car *c) {
    // TODO: return pointer to embedded engine (const‑correct)
}

int main(void) {
    struct car m = {.name="Miata", .price=28000, .speed=205, .eng={181, 2.0f}};
    tune(&m, 40);
    printf("%s: %d hp, %d km/h\n", m.name, m.eng.hp, m.speed);
}
```

**Tasks:** Implement `tune` and `get_engine_const`.

**Checkpoint:** HP and speed increased; function returns address of embedded `engine`.

**Stretch:** Add `void retune(struct engine *e, int add_hp)` and call via `retune(&c->eng, ...)`.

---

## Lab 9.8 — Field Offsets, Padding, and Reordering

**Goal:** Observe `sizeof` and `offsetof` to see alignment/padding in memory.

**Starter (lab8.c):**

```c
#include <stdio.h>
#include <stddef.h> // offsetof

struct car {
    char *name;
    float price;
    int   speed;
};

int main(void) {
    printf("sizeof(struct car) = %zu\n", sizeof(struct car));
    printf("offset(name)  = %zu\n", offsetof(struct car, name));
    printf("offset(price) = %zu\n", offsetof(struct car, price));
    printf("offset(speed) = %zu\n", offsetof(struct car, speed));
}
```

**Tasks:**

1. Record results.
2. Reorder fields to `(int speed, float price, char *name)` and recompute.

**Checkpoint:** `sizeof` and offsets may change due to padding.

**Stretch:** Add a `char tag;` field and observe how placement affects padding.

---

## Lab 9.9 — Safe Equality: Per‑Field Comparison

**Goal:** Implement field‑wise equality; avoid `memcmp` pitfalls.

**Starter (lab9.c):**

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct car { char *name; float price; int speed; };

bool car_equal(const struct car *a, const struct car *b) {
    // TODO: compare speed and price directly; compare names with strcmp (handle NULLs)
}

int main(void) {
    struct car x = {"Saturn", 16000.0f, 175};
    struct car y = {"Saturn", 16000.0f, 175};
    printf("equal? %s\n", car_equal(&x,&y) ? "yes" : "no");
}
```

**Tasks:** Implement `car_equal` with proper `NULL` checks for `name`.

**Checkpoint:** Identical cars compare equal.

**Stretch:** Demonstrate why `memcmp(&x,&y,sizeof x)` is not reliable (padding bytes may differ).

---

## Lab 9.10 — Returning Structs vs Pointers (Lifetime)

**Goal:** See copy semantics and lifetime risks.

**Starter (lab10.c):**

```c
#include <stdio.h>
#include <string.h>

struct car { char *name; float price; int speed; };

struct car make_car_copy(void) {
    struct car c = {"Temp", 1.0f, 1};
    return c; // safe: returned by value (copied to caller)
}

struct car *bad_return_ptr(void) {
    struct car c = {"Temp", 1.0f, 1};
    // WARNING: returning address of a local is UB; for demonstration only
    return &c;
}

int main(void) {
    struct car a = make_car_copy();
    printf("copy: %s %.2f %d\n", a.name, a.price, a.speed);

    struct car *p = bad_return_ptr();
    // DO NOT dereference p in real code; lifetime ended.
    (void)p;
}
```

**Tasks:** Compile and read warnings. Do **not** dereference `p`.

**Checkpoint:** Understand: returning by value is safe; returning pointer to local is unsafe.

**Stretch:** Write a safe factory `struct car *make_car_heap(const char*,float,int)` that heap‑allocates.

---

## Lab 9.11 — `typedef` Convenience & `const` Correctness

**Goal:** Reduce verbosity and practice API const‑correctness.

**Starter (lab11.c):**

```c
#include <stdio.h>

typedef struct car {
    char *name; float price; int speed;
} Car;

void print_car(const Car *c) { // const: function promises not to mutate *c
    printf("%-10s $%7.2f %3d km/h\n", c->name, c->price, c->speed);
}

int main(void) {
    Car c = {"Civic", 22000.0f, 190};
    print_car(&c);
}
```

**Tasks:** Convert earlier lab functions to use `Car` and `const` where appropriate.

**Checkpoint:** Cleaner signatures; compiler enforces const safety.

**Stretch:** Try `const char *name` in `Car` and adjust deep‑copy logic (you must allocate and copy from a `const` source).

---

## Lab 9.12 — Flexible Array Member (Advanced)

**Goal:** Store variable‑length names inline with the struct allocation.

**Starter (lab12.c):**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A packed record with the name stored inline after the header
struct car_rec {
    float price;
    int   speed;
    size_t name_len;
    char  name[]; // flexible array member (C99)
};

struct car_rec *car_rec_new(const char *name, float price, int speed) {
    size_t len = strlen(name);
    struct car_rec *r = malloc(sizeof *r + len + 1);
    if (!r) return NULL;
    r->price = price;
    r->speed = speed;
    r->name_len = len;
    memcpy(r->name, name, len + 1);
    return r;
}

int main(void) {
    struct car_rec *r = car_rec_new("Miata", 28000.0f, 205);
    if (!r) return 1;
    printf("%s $%.2f %d\n", r->name, r->price, r->speed);
    free(r);
}
```

**Tasks:** Build and run. Inspect `sizeof(struct car_rec)` and total allocated bytes.

**Checkpoint:** Single allocation holds header + string.

**Stretch:** Store an array of `struct car_rec *` and compute the longest name length.

---

## Lab 9.13 — Minimal Dynamic Vector of `Car`

**Goal:** Implement a tiny growable array for practice with `realloc`.

**Starter (lab13.c):**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char *name; float price; int speed; } Car;

typedef struct {
    Car   *data;
    size_t len, cap;
} CarVec;

void vec_init(CarVec *v) { v->data=NULL; v->len=0; v->cap=0; }

int vec_push(CarVec *v, Car c) {
    if (v->len == v->cap) {
        size_t ncap = v->cap ? v->cap*2 : 4;
        Car *nd = realloc(v->data, ncap * sizeof *nd);
        if (!nd) return -1;
        v->data = nd; v->cap = ncap;
    }
    v->data[v->len++] = c; // shallow copy; OK if names are string literals for now
    return 0;
}

void vec_free(CarVec *v) { free(v->data); }

int main(void) {
    CarVec v; vec_init(&v);
    vec_push(&v, (Car){"Saturn",16000,175});
    vec_push(&v, (Car){"Civic",22000,190});
    for (size_t i=0;i<v.len;i++)
        printf("%s %.0f %d\n", v.data[i].name, v.data[i].price, v.data[i].speed);
    vec_free(&v);
}
```

**Tasks:** Add `vec_find_fastest(const CarVec*)` returning index of max `speed`.

**Checkpoint:** Works for any length; no leaks under AddressSanitizer.

**Stretch:** Make `vec_push` perform a deep copy of `name` when the source name is not a string literal.

---

## Quick Reference & Gotchas

* `.` for structs; `->` for pointers to structs.
* Passing a struct **by value** copies it; mutations don’t affect the caller.
* Returning a struct **by value** is safe (copy). Returning a pointer to a local is **UB**.
* Deep copy pointer fields when independent ownership is required.
* Do not rely on `memcmp` for struct equality (padding). Compare per‑field; use `strcmp` for C strings.
* Alignment/padding can change `sizeof`; reordering fields can reduce size.
* Prefer `const` on read‑only pointer params to enforce and document intent.

## Optional Submission Checklist (per lab)

* [ ] Compiles with `-Wall -Wextra -Wpedantic -fsanitize=address,undefined`.
* [ ] Checkpoint output matches expectations.
* [ ] (Stretch) Completed and noted observations.

---

**End of Module 8 Labs**
