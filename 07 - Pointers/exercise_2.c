#include <stdio.h>

int a = 5;
int *p = &a; // Declare a pointer p and assign it the address of a

int main() {
    printf("Value of a: %d\n", a); // Print the value of a
    printf("Address of a: %p\n", (void*)&a); // Print the address of a
    printf("Value of address '%p' is : %d\n", (void*)&a, *p); // Print the value at the address stored in p
    printf("Address stored in pointer p: %p\n", (void*)p); // Print the address stored in pointer p
    printf("Value at address stored in pointer p: %d\n", *p); // Print the value at the address stored in pointer p
    return 0; // Return 0 to indicate successful execution of the program
}