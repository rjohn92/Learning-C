#include <stdio.h>

int main () {
    float jordan_ppg = 30.1f; // Declare a float variable and initialize it with a value
    float curry_ppg = 24.7; // Declare an integer variable and initialize it with a value
    int curry_stats = curry_ppg; //implicit casting from float to int, truncating the decimal part
    int jordan_stats = (int)jordan_ppg; //explicit casting from float to int
    
    // convert float -> to int 

    // convert unsigned int -> to signed int to see wraparound
    unsigned int u = 4294967295; // Maximum value for a 32-bit unsigned int
    int signed_u = (int)u; // Cast unsigned int to signed int

    printf("Original 'jordan_ppg' value: %.2f\n", jordan_ppg); // Print the float variable with 2 decimal places
    printf("Converted 'jordan_ppg' to int: %d\n", (int)jordan_ppg); // Cast float to int, truncating the decimal part
    printf("Implicit cast of curry_ppg : %d\n", curry_stats); // Print the implicitly casted value
    printf("Explicit cast of jordan_number: %d\n", jordan_stats); // Print the

    printf("-------------------------------------------\n");
    printf("Unsigned int value 'u': %u\n", u); // Print the unsigned int value
    printf("Signed int value after casting 'u': %d\n", signed_u); // Print the signed int value after casting
    printf("Wraparound effect: %d\n", signed_u + 1); // Demonstrate wraparound effect by adding 1 to the signed value

    printf(" ");
    return 0;
}