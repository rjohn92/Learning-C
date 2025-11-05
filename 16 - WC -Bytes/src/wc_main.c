#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "wc_core.h"

// Function to open a file stream for reading bytes from a specified path
static FILE *open_stream(const char *path, int *need_close) {
    if (!path || strcmp(path, "-") == 0) {
        *need_close = 0;
        return stdin;
    }
    FILE *fp = fopen(path, "rb");          // 'rb' keeps counts exact on Windows
    if (!fp) fprintf(stderr, "open %s: %s\n", path, strerror(errno));
    *need_close = (fp != NULL);
    return fp;
}

// Function to display usage information
// p: program name
static void usage(const char *p) {
    fprintf(stderr,
        "Usage: %s [--bytes|--words] [file|-]\n"
        "  --bytes   count bytes (default)\n"
        "  --words   count words\n"
        "  file      path to input file; use '-' or omit for stdin\n",
        p);
}


int main(int argc, char **argv) {
    // designate between bytes/words count based on argv[1] name
    enum { MODE_BYTES, MODE_WORDS } mode = MODE_BYTES;
    const char *path = NULL;

    if (argc < 2 || argc > 3) {
        usage(argv[0]);
        return 2;
    }
    // very small arg parser: [--bytes | --words] [file]
    for (int i = 1; i <argc; i++) {
        if (strcmp(argv[i], "--bytes") == 0 ) {
            mode = MODE_BYTES;
        } else if (strcmp(argv[i], "--words") == 0) {
            mode = MODE_WORDS;
        } else if (path == NULL) {
            path = argv[i];
        } else {
            usage(argv[0]);
            return 2;
        }
    }
    int need_close = 0;
    FILE *fp = open_stream(path, &need_close);
    if (fp == NULL) {
        return 1;       
    }

    size_t out = 0;
    int rc = 0;
    if (mode == MODE_BYTES) {
        rc = count_bytes(fp, &out);
    } else {
        rc = count_words(fp, &out);
    }

    if (need_close) {
        fclose(fp);     
    }
    if (rc == -1) {
        perror("Error during counting");
        return 1;
    } else {
        printf("%zu\n", out);
    }

    return 0;
}