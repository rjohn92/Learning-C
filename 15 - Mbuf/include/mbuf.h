#pragma once

#include <stddef.h>


typedef struct {
    // Placeholder for mbuf structure (e.g., data pointer, length, capacity)
    unsigned char *data;  // Pointer to the buffer data which looks like an array of bytes (aka these look like chars such as 'A', 'B', etc.)
    size_t length; // Current length of data in the buffer which tells us how many bytes are currently used in the buffer)
    size_t capacity; 
} Mbuf;


/* Lifecycle */
void mbuf_init(Mbuf *b);
void mbuf_free(Mbuf *b);


// Operations
int mbuf_push_byte(Mbuf *b, unsigned char byte);
int mbuf_reserve(Mbuf *b, size_t need);
