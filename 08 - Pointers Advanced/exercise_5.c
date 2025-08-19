# include <stdio.h>
# include <stdlib.h>

void allocate_ints(int size) {
    int *arr = malloc(size * sizeof(int)); // Allocate memory for N integers
    if (!arr) {
        perror("Memory allocation failed\n");
        return 1;
    }
   //double the values in the array
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 2; // Initialize each element to double its index
    }
}