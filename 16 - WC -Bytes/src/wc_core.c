#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>  
#include "wc_core.h"




// Function to read bytes from stdin if no path is provided (i.e argc ==1)
// *fp = open_stream(path);
// *out = total bytes read
int count_bytes(FILE *fp, size_t *out) {
    unsigned char buffer[4096];
    size_t total = 0;
    for (;;) {
        size_t n = fread(buffer, 1, sizeof(buffer), fp);
        if (n >0) { 
            total += n;
    } else 
        break;
    }
    if (ferror(fp)) {
        fprintf(stderr, "fread failed: %s\n", strerror(errno));        
        return -1;
    }
    *out = total;
    return 0;
}

// fp : file pointer to read from
// out: pointer to size_t to store word count else we return -1 on error which is checked by caller 

int count_words(FILE *fp, size_t *out) {
    unsigned char buffer[4096];
    size_t total_words = 0;
    int in_word = 0; // Flag to track if we are inside a word

    for(;;) {
        size_t n = fread(buffer, 1, sizeof(buffer), fp);
        if (n ==0) {
            if (ferror(fp)) {
                fprintf(stderr, "fread failed: %s\n", strerror(errno));
                return -1;
            }
            break; // EOF reached
        }
        for (size_t i = 0; i < n; i++) {
            if (isspace(buffer[i]) && in_word== 1) {
                    in_word = 0; // Exiting a word
                } else {
                    // Still outside a word
                    if (in_word==0) {
                        total_words++; // Starting a new word
                        in_word = 1;
                    }
                }
            }
        
    }
    *out = total_words;
    return 0;
}



