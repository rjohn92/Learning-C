# include <stdio.h>
# include <stdlib.h>
# include <assert.h>


int *allocate_ints(int size) {
    int *arr = malloc(size * sizeof(int)); // Allocate memory for N integers
    if (!arr) {
        perror("Memory allocation failed\n");
        exit(1);
    }
   //double the values in the array
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 2; // Initialize each element to double its index
    }

    return arr; // Return the pointer to the allocated array
}
int guarded_writer(int *arr, int size, int index, int value) {
    if (index < 0 || index >= size) {
        printf("Error: Index %d is out of bounds. The array size is %d.\n", index, size);
        return -1; // Return -1 to indicate an error
    }
    assert(index >= 0 && index < size); // Ensure index is within bounds
    arr[index] = value; // Write value to the array at the specified index
    return 0; // Return 0 to indicate success
}


int main() {

    int size = 10; // Define the size of the array
    int *arr = allocate_ints(size); // Call the function to allocate and initialize the array

    for (int i = 0; i < size; i++) {
        printf("Index: %d ", i);
    }
    for (int i = 0; i < size; i++) {
                printf("Value: %d ", arr[i]);

    }
    guarded_writer(arr, size, 2, 20); // Write value 20 at index 2
    free(arr); // Free the allocated memory
}