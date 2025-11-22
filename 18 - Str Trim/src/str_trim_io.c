#define _POSIX_C_SOURCE 200809L
#include "str_trim_io.h"
#include "str_trim_core.h"
#include <stdlib.h>
#include <string.h>


// Function to process an input stream, trimming each line and outputting the result
// in: input file stream
// returns: 0 on success, 1 on I/O error
int process_stream(FILE *in) {
    char *buf = NULL;
    size_t cap = 0;
    ssize_t nread;
    while ((nread = getline(&buf, &cap, in)) != -1) {
        if (nread >0 && buf[nread -1] == '\n') {
            buf[nread -1] = '\0'; // remove newline

        }
        if (nread >0 && buf[nread -1] == '\r') {
            buf[nread -1] = '\0'; // remove newline

        }
        trim_inplace(buf);       // call your function
        if (fputs(buf, stdout) == EOF || fputc('\n', stdout) == EOF) {
            perror("fputs/fputc");
            free(buf);
            return 1;
        }

    }
    if (ferror(in)) {
        perror("getline");
        free(buf);
        return 1;
    }
    free(buf);
    return 0;
}
