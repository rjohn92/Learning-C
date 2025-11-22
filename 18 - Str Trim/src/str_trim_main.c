#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_trim_core.h"
#include "str_trim_args.h"
#include "str_trim_io.h"

// Structure to hold command-line options


// Portable strdup replacement (ISO C)
static char *sdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (!p) {
        return NULL;
    }
    memcpy(p, s, n);  // copies the '\0' too
    return p;
}


int main(int argc, char **argv) {

    struct options opt = {0}; 
    int parse_rc = parse_args(argc, argv, &opt, stderr);
    if (parse_rc != 0) {
        return 2; 
    }

    if (opt.file_path) {
        FILE *fp = fopen(opt.file_path, "r");
        if (!fp) {
            perror(opt.file_path);
            return 1;
        }
        int rc = process_stream(fp);
        fclose(fp);
        return rc;
    }

    if (opt.use_stdin) {
        return process_stream(stdin);
    }



    char *buf = sdup(opt.string_arg);
    if (!buf){ 
        perror("malloc"); return 1; 
    }

    size_t n = trim_inplace(buf);    // call your function
    (void)n;                            // (unused for now)
    puts(buf);                          // show result
    if (opt.print_len) {
        printf("%zu\n", trimmed_length(opt.string_arg));
    }
    free(buf);
    return 0;


}