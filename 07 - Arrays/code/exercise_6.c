#include <stdio.h>

void create_array(int *arr, int len) {
    for (int i = 0; i< len; i++) {
        arr[i] = (i +1)* 2; // Initialize each element to double its index
    }
}
int main () {

    // Declare an array of 5 integers and initialize with known values.
    int arr[5];
    int size = sizeof(arr) / sizeof(arr[0]);
    create_array(arr, size); // Populate the array with values
    
    printf("------------------------------------------\n");
    printf("Printing using array notation...\n");

    //Print all 5 values...

    for (int i = 0; i < size; i++) {
        printf("Value at index '%d' is: %d\n", i, arr[i]); // Print each value using array notation
    }

    //...then attempt to print a[5], a[6]
    printf("Attempting to print out of bounds values:\n");
    printf("Value at index '5' is: %d\n", arr[5]); // This will likely cause undefined behavior
    printf("Value at index '6' is: %d\n", arr[6]); // This will likely cause undefined behavior
    
    return 0; // Return 0 to indicate successful execution of the program
}