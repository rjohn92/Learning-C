#include <stdio.h>

int main() {
    int temperature = 70; // Declare an integer variable named temperature and initialize it with the value 70
    if (temperature >= 90) {
        printf("It's a hot day. \n"); // Print a message indicating it's a hot day
    } else if (temperature >= 80) {
        printf("It's pretty warm. \n"); // Print a message indicating it's pretty warm
    } else if (temperature >= 70) {
        printf("It's a nice day. \n"); // Print a message indicating it's a nice day
    } else if (temperature >= 60) {
        printf("It's a bit chilly. \n"); // Print a message indicating it's a bit chilly
    } else {
        printf("It's cold. \n"); // Print a message indicating it's cold
    }
    return 0; // Return 0 to indicate successful execution of the program
}