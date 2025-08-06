# Module 8: Structures and Data Organization in C

---

## 📚 Learning Objectives

By the end of this module, you will be able to:

* Define and use C structs to organize complex data.
* Use pointers with structs (including nested structs and arrays of structs).
* Understand and utilize enums and unions.
* Apply best practices for organizing data in C for real-world security, RE, or CNO tasks.

---

## 1. Why Structures? (Motivation)

Primitive types (`int`, `char`, `float`) are limiting when modeling real-world entities.

**Structures (`struct`s)** let you group related variables—**different types under one roof**.

> Example use cases: Modeling a TCP packet, a user record, a PE/ELF header, or a binary protocol structure.

```c
struct Point {
    int x;
    int y;
};
```

---

## 2. Defining and Using Structs

### Syntax

```c
struct StructName {
    type member1;
    type member2;
    ...
};
```

### Declaring and Accessing

```c
struct Point pt1;
pt1.x = 10;
pt1.y = 20;
printf("(%d, %d)\n", pt1.x, pt1.y);
```

### Typedef (for convenience)

```c
typedef struct {
    int x, y;
} Point;

Point pt2 = { .x = 5, .y = 15 };
```

---

## 3. Struct Pointers

Pointers to structs are everywhere in real C code (heap-allocated structs, passing large data to functions, linked lists, etc).

* **Access members:**

  * Direct struct: `pt1.x`
  * Pointer to struct: `pt_ptr->x` (equivalent to `(*pt_ptr).x`)

```c
Point *pt_ptr = &pt2;
printf("Y value: %d\n", pt_ptr->y); // pt_ptr->y == (*pt_ptr).y
```

* **Heap allocation:**

  * `Point *heap_pt = malloc(sizeof(Point));`
  * Always `free()` heap-allocated structs!

---

## 4. Nested Structs and Arrays of Structs

### Nested Structs

```c
typedef struct {
    char name[32];
    int id;
} User;

typedef struct {
    User owner;
    char filename[64];
    int size;
} FileMeta;

FileMeta doc = { .owner = {"alice", 1}, .filename = "doc.txt", .size = 1024 };
printf("Owner: %s\n", doc.owner.name);
```

### Arrays of Structs

```c
User users[10];
users[0].id = 100;
strcpy(users[0].name, "bob");
```

---

## 5. Structs as Function Arguments and Return Values

Passing large structs by value is expensive (copies data).

* **Pass a pointer** for efficiency:

```c
void print_user(const User *u) {
    printf("ID: %d, Name: %s\n", u->id, u->name);
}

print_user(&users[0]);
```

---

## 6. Enums: Named Integer Constants

Enums make code more readable (especially for states, error codes, types).

```c
typedef enum {
    STATUS_OK = 0,
    STATUS_ERROR = 1,
    STATUS_TIMEOUT = 2
} Status;

Status s = STATUS_ERROR;
if (s == STATUS_ERROR) {
    printf("Error occurred!\n");
}
```

---

## 7. Unions: Memory Overlays

A `union` lets different fields share the *same* memory. Useful for protocols, type punning, or variant records.

```c
typedef union {
    int i;
    float f;
    char str[4];
} Data;

Data d;
d.i = 0x41424344; // Set as int, reinterpret as bytes
printf("First char: %c\n", d.str[0]); // Prints 'D' on little-endian
```

**Warning:** Only use one member at a time.

---

## 8. Real-World Data Organization: Best Practices

* **Group related data:** Use structs for clarity, maintainability, and safe memory layout.
* **Avoid excessive nesting:** Too many layers of structs can confuse code.
* **Be explicit with sizes:** Useful in CNO for parsing binary data/headers.
* **Prefer enums to magic numbers:** Improves code auditability.
* **Document your struct layouts:** Especially if mapping to protocols or binary formats.

---

## 9. Example: Parsing a Binary File Header

```c
typedef struct {
    char magic[4]; // 'MZ', etc.
    uint16_t version;
    uint32_t file_size;
} __attribute__((packed)) FileHeader;

// Read header from file
FILE *fp = fopen("myfile.bin", "rb");
FileHeader hdr;
fread(&hdr, sizeof(hdr), 1, fp);
fclose(fp);
```

---

## 10. Summary & Next Steps

* Structs let you model real-world data structures in C
* Pointers unlock efficient manipulation (esp. in RE/security work)
* Enums/unions help manage state and variant data
* Solid data organization is crucial for CNO/RE, binary analysis, and exploit dev

> Next: Practice with real-world structs—parse a protocol header, create a linked list, or implement a simple config loader.

---

### 🔗 Further Reading / Exercises

* K\&R C, Ch. 6
* [Beej’s Guide: Data Structures](https://beej.us/guide/bgc/html/#data-structures)
* Do: Write a program to parse a PE/ELF header and print fields
* Bonus: Try a simple linked list of structs
