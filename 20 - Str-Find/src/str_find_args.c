#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "str_find_args.h"
// Helper to print usage and return 2

int usage_with(FILE *err, const char *prog, const char *msg) {
    if (msg && *msg) {
        fprintf(err, "error: %s\n", msg);
    }
    print_usage(err, prog);
    return 2;
}

// Print usage information to 'to' stream
// to: output stream
// prog: program name
void print_usage(FILE *to, const char *prog) {
    fprintf(to,
        "Usage:\n"
        "  %s STRING\n"
        "  %s -                (read from stdin)\n"
        "  %s --file PATH      (read from file)\n"
        "Options:\n"
        "  --print-len         Print trimmed length on next line\n"
        "  --chars SET         Trim these characters (later)\n",
        prog, prog, prog);
}