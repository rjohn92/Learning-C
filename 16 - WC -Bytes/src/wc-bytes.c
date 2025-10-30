#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>  

// Function to open a file stream for reading bytes from a specified path
static FILE* open_stream(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "Error opening file: %s\n", path);
        return NULL;
    }
    return fp;
}
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

int count_word(FILE *fp, size_t *out) {
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
            if (isspace(buffer[i])) {
                if (in_word==1) {
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
    }
}

void usage(const char *prog) {
    fprintf(stderr, "Usage: %s [file]\n", prog);
    fprintf(stderr, "  file   optional file path (stdin if omitted)\n");
}


int main(int argc, char **argv) {
    
}