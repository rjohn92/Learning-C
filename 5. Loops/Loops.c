#include <stdio.h>

int main() {
    int count = 10;
    char nickname[] = "Buddy"; // Declare a character array (string) variable named nickname and initialize it with "Buddy"

    //For loop to count from 1 to count
    printf("Starting our 'for' loop...\n");

    for (size_t i = 1; i <= count; i++) {
        if (i < 10) {
            printf("Sorry, %s! We're only at %zu. Still counting... \n", nickname, i);
        } else {
            printf("Alright, %s. We counted to %zu. The count is over. \n", nickname, i);
        }        
    }
    
    printf("-----------------------------------------------------------------\n");
    printf("\nStarting our 'while' loop...\n"); // Print a message indicating the counting is done
    count = 0; // Reset count to 0
    while (count < 10) {
        count++; // Increment count by 1
        printf("Count is now %d.\n", count); // Print the current value of count
    }
 

    printf("\n-----------------------------------------------------------------\n");
    printf("\nStarting our 'do while' loop...\n"); // Print a message indicating the counting is done
    do {
        printf("Count is now %d.\n", count); // Print the current value of count
        count--; // Decrement count by 1
    } while (count >= 0); // Continue the loop until count hits 0

       return 0;
}