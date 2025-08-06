Module 8: Hands-on Labs – Structures & Data Organization

Lab 1: Basic Structs

Objective: Define and use a struct to represent a 2D point.

Tasks:

Define a struct Point with int x and int y.

Write a function to print a Point.

Initialize a point and print its values.

Lab 2: Pointers to Structs

Objective: Manipulate structs via pointers.

Tasks:

Write a function void set_point(Point *p, int x, int y) that sets the members using a pointer.

Allocate a Point on the heap, set its values, print, and then free it.

Lab 3: Nested Structs and Arrays of Structs

Objective: Organize data using nested structs and arrays.

Tasks:

Define a struct User (name, id).

Define a struct FileMeta with a User owner, filename, and file size.

Create an array of FileMeta entries and print details for each.

Lab 4: Enums in Practice

Objective: Use enums to model and print program state.

Tasks:

Define an enum for Status (STATUS_OK, STATUS_ERROR, STATUS_TIMEOUT).

Write a function that takes a Status and prints a message.

Test the function with all possible states.

Lab 5: Unions for Type-Punning

Objective: Use a union to reinterpret memory as different types.

Tasks:

Define a union with an int, a float, and a char[4].

Assign an integer value, then print the bytes using the char array.

Explain what you observe about endianness and memory layout.

Lab 6: Real-World CNO Mini-Project – Binary Header Parsing

Objective: Parse a custom binary file header using structs, enums, and proper data organization.

Tasks:

Design a struct to represent a file header (e.g., magic[4], version, file_size, status enum).

Simulate reading from a file (use a buffer or fread) and fill the struct.

Print each field, and interpret the status using your enum.

Lab 7: Bonus – Linked List of Structs

Objective: Create and traverse a simple linked list of structs.

Tasks:

Define a struct Node with an int value and a pointer to the next node.

Dynamically allocate 3 nodes, link them, and traverse/print all values.

Tip: After completing each lab, write a 2–3 sentence summary: What did you learn? Where could this apply in real CNO/RE work?