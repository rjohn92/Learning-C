# include <stdio.h>
# include <stdlib.h>

int main () {
    int *p = NULL; // Declare a pointer and initialize it to NULL
//    *p = 1; // Attempt to assign a value to the pointer (this will cause a segmentation fault)

//    printf("%p\n", (void*)&p); // This line will not be executed due to the segmentation fault
    

    free(p); // Free the pointer (not necessary here since p is NULL, but good practice)

    printf("Pointer p is initialized to NULL and not dereferenced.\n");
    printf("Address of pointer p: %p\n", (void*)&p); // Print the address of the pointer itself
    
    free(p); // Free the pointer (not necessary here since p is NULL, but good practice)
    p = NULL; // Set the pointer to NULL again to avoid dangling pointer issues
    
    return 0; // Return 0 to indicate successful execution of the program
}