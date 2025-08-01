#include <stdio.h>

int main () {
    int x = 42; 
    printf("Value of x: %d\n", x); // Print the value of x
    int *p = &x; // Declare a pointer p and assign it the address of x

    printf("Address of x: %p\n", (void*)&x); // Print the address of x

}


