#include <stdio.h>


int max = 15; // Declare a global variable named max and initialize it with the value 15
int main() {
    
    for (size_t i = 1; i <=max; i++) {
        if (i%2==0) {
            printf("%zu is even.\n", i); // Print if the number is even
        } else {
            printf("%zu is odd.\n", i); // Print if the number is odd
        }
    };
    printf("Done counting to %d.\n", max); // Print a message indicating the counting is done
    return 0;
}