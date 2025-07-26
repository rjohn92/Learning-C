#include <stdio.h>

int main () {

    int any_int_value = 21;
    float any_float_value = 92.7;
    char letter = 'A';
    size_t triangle_length = 3;
    const float PI= 3.14159f;
    printf("'any_int_value': %d\n", any_int_value);
    printf("'any_float_value': %.2f\n", any_float_value);
    printf("'letter': %c\n", letter);
    printf("'triangle_length' value: %zu\n", triangle_length);
    printf("'PI' value: %.5f\n", PI);
    

    printf("Size of char: : %zu\n",sizeof(char));
    printf("Size of size_t: %zu\n", sizeof(size_t));

    int a = 999; // Declare an integer variable with a large value
    printf("Size of 'a': %zu\n", sizeof(a));

    int large_number = 2147483647; // Maximum value for a 32-bit signed integer
    printf("Size of 'large_number': %zu\n", sizeof(large_number));

    printf("Size of '3.14' is: %zu\n", sizeof 3.14);   // Prints 8 on my system
    return 0;
}


// Questions

//What’s the difference in output between `sizeof(char)` and `sizeof(size_t)`?


// * What happens if you try to modify a `const` variable? A `#define`?