#include <stdio.h>

int add_ten(int number) {
    return number + 10; // Function to add 10 to the input number...simple
}

int main() {
    int input_number = 5; // Declare an integer variable and initialize it with a value
    printf("Input number: %d\n", input_number); // Print the input number
    
    int result = add_ten(input_number); // Call the function and store the result
    printf("Result after 'add_ten' function: %d\n", result); // Print the result after adding 10
    return 0; // Return 0 to indicate successful execution of the program
}