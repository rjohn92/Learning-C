#include <stdio.h>

int main() {
    int *p = NULL; // Declare a pointer and initialize it to NULL
    *p = -1; // Attempt to assign a value to the pointer (this will cause a segmentation fault)
    return 0; // Return 0 to indicate successful execution of the program
    }

    