# include <stdio.h>

int main() {

    int size = 6; // Size of the array
    int arr[size]; // Declare an array of 6 integers
    int *ptr = arr; // Pointer to the start of the array

    // We just initialize the array with some values
    for (int i = 0; i < size; i++) {    
        arr[i] = (i + 1)* 2; 
    }

    // Print the values using pointer notation
    printf("Printing values using pointer notation:\n");

    for (int i = 0; i < size; i++) {
        printf("Index: '%d' || Address: '%p' || Value: '%d'\n", i,(void*)(ptr + i), *(ptr + i));
    }
  

    return 0; // Return 0 to indicate successful execution of the program
}