#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mbuf.h"

//This project is meant to implement a memory buffer (mbuf), which is a dynamic array that can grow as needed to hold data.
// We use buffers to temporarily store data in memory before processing or writing it out. 
// For example, when reading data from a file or network socket, we might read chunks of data into a buffer before processing it. 


//Our goal is to create functions to initialize, free, append data to, and manage the memory buffer efficiently. 
// A workflow might involve:
// 1. Initializing an mbuf structure to hold our data. 
// 2. Appending data to the mbuf, which may involve reallocating memory if the current capacity is exceeded.
// 3. Freeing the mbuf when done to avoid memory leaks. {
    // Free any allocated memory associated with the mbuf
// 4. Additional utility functions as needed (e.g., resizing, clearing the buffer).




void mbuf_init(Mbuf *buff) {
    // we take in a pointer to an mbuf structure and call that pointer "buff"
    // Initialize the mbuf structure members to default values 
    // (e.g., NULL pointers, zero lengths)
    buff->data = NULL; 
    buff->length = 0;
    buff-> capacity = 0;
}

void mbuf_free(Mbuf *buff) {
    if (buff == NULL) {
        return; // Nothing to free
    }
    free(buff->data); // Free the allocated data buffer
    buff->data = NULL; // Set pointer to NULL to avoid dangling pointer
    buff->length = 0; // Reset length
    buff->capacity = 0; // Reset capacity
}
int mbuf_reserve(Mbuf *buff, size_t need) {
    if (buff->capacity >= need) {
        return 0; // Already have enough capacity
    } 
    size_t new_capacity = buff->capacity ? buff->capacity : 1;
    while (new_capacity < need) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = need; // Prevent overflow
            break;
        }

        new_capacity *= 2; // Double the capacity
    }
    unsigned char *new_data = realloc(buff->data, new_capacity);

    if (new_data == NULL) {
        errno = ENOMEM;      
        return -1; // Memory allocation failed
    }
    buff->data = new_data;
    buff->capacity = new_capacity;
    return 0;
}

int mbuf_push_byte(Mbuf *buff, unsigned char byte) {
    if (mbuf_reserve(buff, buff->length +1) !=0) {
        return -1; // Memory allocation failed
    }
    buff->data[buff->length] = byte; // Append the byte to the end of the buffer
    buff->length +=1; // Increase the length of the buffer
    return 0;
}

void mbuf_clear(Mbuf *buff) {
    buff->length = 0; // Simply reset the length to zero
}


int main() {
    // Example usage of mbuf.c functions would go here
    return 0;
}