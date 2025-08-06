#include <stdio.h>
#include <string.h> // Include the standard library for string manipulation functions


int main () {
    
    int nums [5]; 
    for (int i = 0; i<5; i++) {
        nums[i] = (i +1) * 10; // Initialize the array with values 1 to 5
    }

    // Print the values in the array
    for (int i = 0; i<5; i++) {
        int *ptr = &nums[i];  
        printf("Value at index '%d': %d and at address %p\n", i, nums[i], (void*)ptr); // Print the value at each index
    }
    

    return 0; // Return 0 to indicate successful execution of the program
}
