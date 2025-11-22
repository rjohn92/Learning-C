#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "echo_args_core.h"


// Function to display usage information
// p: program name
static void usage(const char *p) {
    fprintf(stderr,
        "Usage: %s [--argc|--argv] [args|-]\n"
        "  --argc   count total args\n"
        "  --argv   separate args\n"
        "  args     get args from command line; use '-' or omit for stdin\n",
        p);
}

int main(int argc, char **argv) {
    enum { MODE_ARGC, MODE_ARGV } mode = MODE_ARGC;

    int rc = 0;
    if (argc < 2) {
        usage(argv[0]);
        return 2;
    }
    if (strcmp(argv[1], "--argc") == 0 ) {
        mode = MODE_ARGC;
    } else if (strcmp(argv[1], "--argv") == 0) {
        mode = MODE_ARGV;
    } else {
        usage(argv[0]);
        return 2;
    }

    if (mode == MODE_ARGV) {
        rc = print_argv(argc, argv);
        return rc;
    } else if (mode == MODE_ARGC) {
        rc = print_argc(argc);
        return rc;
    }

    return rc;


}