#include <stdio.h>

void set_to_zero(int *ptr) {
    *ptr = 0; // Set the value at the address pointed to by ptr to zero
}

int main() {
    int x = 42; // Declare an integer variable and initialize it with a value
    printf("Original value of number: %d\n", x); // Print the original value of x
    printf("Address of number: %p\n", (void*)&x); // Print the address of x
    printf("Value at address '%p' is: %d\n", (void*)&x, x); // Print the value at the address of x

    set_to_zero(&x); // Call the function with the address of number

    printf("Value of number after set_to_zero: %d\n", x); // Print the modified value of number
    return 0; // Return 0 to indicate successful execution of the program
}