#include <stdio.h>

/* Print the argc value (number of command-line arguments). */
int print_argc(int argc) {
    printf("Number Args: %d\n", argc-2); // Exclude program name and mode argument
    return 0;
}

int print_argv(int argc, char **argv) {
    for (int i = 2; i < argc; i++){
        printf("Arg %d: %s\n", i-1, argv[i]); // Start from index 2 to skip program name and mode argument
    }
    return 0;

}