#include <stdio.h>
#include <stdlib.h>

int main () {
    int size = 10; // Initial size of the array
    int *arr = malloc(size*sizeof(int)); // Allocate memory for 10 integers

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit if memory allocation fails
    }
    printf("\n-----------------------------------------\n");

    // Print the initial values of the array (may have garbage values)
    printf("Initial array values:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i)); // Print each value using pointer arithmetic
    }
    // Initialize the array with some values
    for (int i = 0; i < size; i++) {
        arr[i] = (i +1) * 5; // Assign values to the array
    }
        printf("\n-----------------------------------------\n");

    printf("\nArray values before resizing:\n");
    for (int i = 0; i< size; i++) {
        printf("%d ", arr[i]); // Print each value
    }
    printf("\n-----------------------------------------\n");

    int new_size = size * 2; // New size for the array
    arr = realloc(arr, new_size * sizeof(int)); // Resize the allocated memory to hold 15 integers
    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        return 1; // Exit if memory reallocation fails
    }

    // Initialize the new elements in the resized array
    for (int i = size; i < new_size; i++) {
        arr[i] = (i + 1) * 5; // Assign values to the new elements
    }


    printf("\nArray values after resizing:\n");
    for (int i = 0; i< new_size; i++) {
        printf("%d ", *(&arr[i])); // Print each value

    }
    printf("\n-----------------------------------------\n");

    
    return 0; // Return 0 to indicate successful execution of the program



}