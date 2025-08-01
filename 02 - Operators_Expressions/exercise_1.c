#include <stdio.h>

int main () {

    int n1 = 5;
    int n2 = 3;

    printf("Sum of %d and %d: %d\n", n1, n2, n1+n2); // Print the sum")
    printf("Difference of %d and %d: %d\n", n1, n2, n1-n2); // Print the difference
    printf("Product of %d and %d: %d\n", n1, n2, n1*n2); // Print the product
    printf("Quotient of %d and %d: %d\n", n1, n2, n1 / n2); // Print the quotient
    printf("Remainder of %d and %d: %d\n", n1, n2, n1 % n2); // Print the remainder

    int negative_n1 = -n1; // Negate n1

    printf("Sum of %d and %d: %d\n", negative_n1, n2, negative_n1 + n2); // Print the sum")
    printf("Difference of %d and %d: %d\n", negative_n1, n2, negative_n1 - n2); // Print the difference
    printf("Product of %d and %d: %d\n", negative_n1, n2, negative_n1*n2); // Print the product
    printf("Quotient of %d and %d: %d\n", negative_n1, n2, negative_n1 / n2); // Print the quotient
    printf("Remainder of %d and %d: %d\n", negative_n1, n2, negative_n1 % n2); // Print the remainder
}