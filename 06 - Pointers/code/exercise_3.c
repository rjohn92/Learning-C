#include <stdio.h>

int main() {

    int x = 10; // Declare an integer variable and initialize it with a value
    int *p = &x; // Declare a pointer p and assign it the address of a

    printf("Value of x: %d\n", x); // Print the value of x
    printf("Address of x: %p\n", (void*)&x); // Print the address of x

    printf("Value of address '%p' is: %d\n", (void*)&x, *p); // Print the value at the address stored in p

    *p = 200; // Modify the value at the address stored in p
    printf("Modified value of x is: %d\n", x); // Print the modified value of x
    printf("Address stored in x is still: %p\n", (void*)&x); // Print the address stored in x
    printf("But the value at the address '%p' is now: %d\n", (void*)&x,*p); // Print the value at the address stored in pointer p

    return 0; // Return 0 to indicate successful execution of the program
}