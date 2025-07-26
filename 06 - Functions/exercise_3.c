#include <stdio.h>

void try_to_modify (int number) {
    number += 5; // Attempt to modify the input number
    printf("Modified number inside function: %d\n", number); // Print the modified number
}

int main() {
    int original_number = 10; // Declare an integer variable and initialize it with a value
    printf("Original number before function call: %d\n", original_number); // Print the original number
    
    try_to_modify(original_number); // Call the function to attempt to modify the number
    printf("Original number after function call: %d\n", original_number); // Print the original number again to show it remains unchanged

    return 0; // Return 0 to indicate successful execution of the program
}
