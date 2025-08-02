#include <stdio.h>

void double_values(int *arr, int len) {
    for (int i = 0; i<len; i++) {
        arr[i] = arr[i] * 2;
    }

}

int main() {
    int arr[5];
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Enter %d integers:\n", size);
    for (int i = 0; i< size; i++) {
        printf("Element %d: ", i + 1); // Prompt for each element
        scanf("%d", &arr[i]); // Read the input value into the array
    }
    double_values(arr, size); // Call the function to double the values in the array
    printf("The doubled values are:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // Print each doubled value
    }
    printf("\n");
    return 0; // Return 0 to indicate successful execution of the program
}