#include <stdio.h>

int main() {
    int count = 10;
    char nickname[] = "Buddy"; // Declare a character array (string) variable named nickname and initialize it with "Buddy"
    for (size_t i = 1; i <= count; i++) {
        if (i < 10) {
            printf("Sorry, %s! We're only at %zu. Still counting... \n", nickname, i);
        } else {
            printf("Alright, %s. We counted to %zu. The count is over. \n", nickname, i);
        }        
    }
    
    
    return 0;
}