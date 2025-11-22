
#include "str_trim_args.h"

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


// Parse command-line arguments into 'out' structure
// argc, argv: command-line arguments
// out: pointer to options structure to fill
// err: stream to print errors to
// returns: 0 on success, 2 on usage error
int parse_args(int argc, char **argv, struct options *out, FILE *err) {
    if (!out) return 2;
    // defaults
    out->file_path = NULL;
    out->use_stdin = 0;
    out->print_len = 0;
    out->cutset    = NULL;
    out->string_arg= NULL;

    if (argc < 2) {
        return usage_with(err, argv[0], "no arguments");
    }

    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];

        if (strcmp(a, "--help") == 0 || strcmp(a, "-h") == 0) {
            print_usage(err, argv[0]);
            return 2;
        } else if (strcmp(a, "--print-len") == 0) {
            out->print_len = 1;

        } else if (strcmp(a, "--chars") == 0) {
            i++;
            if (i >= argc) {
                return usage_with(err, argv[0], "--chars requires a SET");
            }
            out->cutset = argv[i];

        } else if (strcmp(a, "--file") == 0) {
            i++;
            if (i >= argc) {
                return usage_with(err, argv[0], "--file requires a PATH");
            }
            if (out->use_stdin)  {
                return usage_with(err, argv[0], "cannot combine --file with stdin (-)");
            }   
            if (out->string_arg) {
                return usage_with(err, argv[0], "cannot combine --file with a STRING");
            }
            out->file_path = argv[i];

        } else if (strcmp(a, "-") == 0) {
            if (out->file_path)  {
                return usage_with(err, argv[0], "cannot combine stdin (-) with --file");
            }
            if (out->string_arg) {
                return usage_with(err, argv[0], "cannot combine stdin (-) with a STRING");
            }
            out->use_stdin = 1;

        } else if (a[0] == '-') {
            return usage_with(err, argv[0], "unknown option");

        } else {
            // positional STRING
            if (out->use_stdin || out->file_path)
                return usage_with(err, argv[0], "positional STRING conflicts with stdin or --file");
            out->string_arg = a;
        }
    }

    if (!(out->file_path || out->use_stdin || out->string_arg))
        return usage_with(err, argv[0], "no input source (STRING, -, or --file PATH)");

    return 0;
}
