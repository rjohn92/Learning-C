#include <stdio.h>

int main() {
    int n1 =23;
    int n2 = 8;
    int n3 = 35;

    printf("%d == %d: %d\n", n1, n2, n1 == n2); // Check if n1 is equal to n2 (should evaluate to 0)
    printf("%d != %d: %d\n", n1, n2, n1 != n2); // Check if n1 is not equal to n2 (should evaluate to 1))
    printf("%d < %d: %d\n", n1, n2, n1 < n2); // Check if n1 is less than n2 (should evaluate to 0)
    printf("%d < %d and %d < %d: %d\n", n1, n2, n2, n3, (n1 <n2) && (n2 < n3)); // Check if n1 is less than n2 and n2 is less than n3 (should evaluate to 0)

    return 0;
}