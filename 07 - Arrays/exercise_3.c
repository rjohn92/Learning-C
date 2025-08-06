#include <stdio.h>

int sum_array(int arr[], size_t size) {
    int sum = 0; // Initialize sum to 0
    for (int i = 0; i < size; i++) { // Loop through each element of the array
        sum += arr[i]; // Add each element to the sum
    }
    return sum; // Return the total sum of the array elements
}


void print_max_min(int arr[], size_t size) {

    int max = arr[0]; 
    int min = arr[0];

    for (int i = 0; i<size; i ++) {
        if (arr[i]<min) {
            min = arr[i];
        } 
        if (arr[i]> max) {
            max = arr[i];
        }
    }
    printf("The min value is: %d\n", min);
    printf("The max value is: %d\n", max);
}

int main() {
    int size = 6; // Declare the size of the array
    int arr[size]; // Declare an array of integers with the specified size

    //Prompt the user to enter values for the array
    printf("Enter %d integers:\n", size);
    for (int i = 0; i< size; i++) {
        printf("Element %d: ", i + 1); // Prompt for each element
        scanf("%d", &arr[i]); // Read the input value into the array
    }


    printf("The sum of the array elements is: %d\n", sum_array(arr, size)); // Call the function to calculate and print the sum
    
    print_max_min(arr, size);

    return 0; // Return 0 to indicate successful execution of the program
}