#include <stdio.h>
#include <string.h> // Include the standard library for string manipulation functions


int main() {
    int numbers[5] = {3,7,11,22,44}; // Declare and initialize an array of integers named numbers with 5 elements
    for (int i = 0; i < 5; i++) { // Loop through each element of the array
        printf("Element %d: %d\n", i, numbers[i]); // Print the index and value of each element in the array
        }
    
    char nickname[] = {"Coder"}; // Declare and initialize a character array (string) named nickname with 5 characters}
        for (int i = 0; i < 5; i++) {   // Loop through each character of the string
            printf("Your nickname is: %c\n", nickname[i]); // Print each character of the string
        }
    printf("Your nickname '%s' is %ld digits long\n", nickname, strlen(nickname)); // Print the length of the string using strlen function from string.h
    return 0; // Return 0 to indicate successful execution of the program
};
