#include <stdio.h>

// Function to check if a number is positive or negative
void check_number(int number) {
    if (number > 0 && number %2==0) {
        printf("The number '%d' is positive\n", number);
    } else if (number < 0 ) {
        printf("The number '%d' is negative\n", number);
    } else {
        printf("the entered number is zero\n");
    }
}

int main() {
    
    int n1 = 6;
    int n2 = -3;
    int n3 = 0;

    check_number(n1);
    check_number(n2);
    check_number(n3);

    return 0;
}