#include <stdio.h>
#include <stdlib.h>



void *bad_function() {
    int local = 42;
    printf("\n%p\n", (void*)&local); // Returning address of a local variable (undefined behavior)
}

int main() {
    int stack_arr[4] = {1, 2, 3, 4}; // Declare and initialize an array on the stack
    int *heap_arr = malloc(4 * sizeof(int)); // Allocate memory for an array on the heap

    if (heap_arr==NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Stack array address: %p\n", (void*)stack_arr);
    printf("Heap array address: %p\n", (void*)heap_arr);


    bad_function();
    return 0;
}

