#include <stdio.h>

void print_n_elements(int *arr, int len) {
    int *ptr = arr; // Pointer to the start of the array
    for (int i = 0; i < len; i++) {
        printf("Address: %p ; Value: %d\n", (void*)(ptr + i),arr[i]);
    }   
}

int main() {
    int arr[10]; // Declare an array of 10 integers
    for (int i = 0; i< 10; i++) {
        arr[i] = (i + 1) *5; // Initialize the array with multiples of 5
    }
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array

    int start = 0; // Starting index for printing
    int end = 4; // Ending index for printing

    printf("Printing elements from indicies: %d to %d\n", start, end);
    print_n_elements(arr, end); // Call the function to print the address of the first element
    printf("-----------------------------------------\n");

    start = 5; // Change starting index for printing
    end = 9; // Change ending index for printing
    printf("Printing elements from indicies: %d to %d\n", start, end);

    print_n_elements(arr + 5, 5); // Call the function to print the address of the first element

    return 0;
}