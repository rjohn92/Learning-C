#include <stdio.h>

int counter = 0; // Global variable

int count_calls() {
    static int calls =0; // Static variable to keep track of calls
    calls++; // Increment the static variable
    printf("Function called %d times.\n", calls);
}


int main() {

    int local_counter = 0; // Local variable
    printf("Global counter before calls: %d\n", counter); // Accessing global variable
    count_calls(); // First call
    printf("Global counter after first call: %d\n", counter); // Accessing global variable
    count_calls(); // Second call
    printf("Global counter after second call: %d\n", counter); // Accessing global variable
    printf("Local counter value: %d\n", local_counter); // Accessing local variable
    local_counter++; // Incrementing local variable
    printf("Local counter after increment: %d\n", local_counter); // Accessing local
    return 0;
}