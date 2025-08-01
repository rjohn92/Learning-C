#include <stdio.h>

// This program demonstrates the use of sizeof operator with arrays and types in C

int length_of_array(char chars[]) {

    int total_bytes = sizeof chars; // Get the total bytes of the array
    int bytes_per_char = sizeof(char); // Get the size of a single char

    printf("Total bytes in chars array: %zu\n", total_bytes); // Print the bytes of chars
    printf("Bytes in chars type: %zu\n", bytes_per_char); // Print the bytes of a single char

    int length = total_bytes/bytes_per_char; // Calculate the length of the array
    printf("Length of chars array: %d\n", length); // Print the length of the array
    return length; // Return the length of the array

}




int main() {
    char s [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g','h','\0'}; // Declare a string array with null terminator
    printf("%zu\n", sizeof s);            // Total bytes of s array
    printf("%zu\n", sizeof(char));         // Bytes per element
    printf("%zu\n", sizeof s / sizeof(char)); // Number of elements
    for (int i = 0; i <= sizeof s / sizeof(char); i++) { // Loop through each element
        printf("%c ", s[i]); // Print each character in the string
    }
    return 0; // Return 0 to indicate successful execution of the program
}