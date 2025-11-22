#ifndef STR_FIND_ARGS_H
#define STR_FIND_ARGS_H

#include <stdio.h>  // FILE
#include <string.h>

struct options {
    const char *file_path;   // NULL if unset
    int  use_stdin;          // 0/1
    int  print_len;          // 0/1
    const char *cutset;      // NULL => default
    const char *string_arg;  // positional STRING, if any
};

void print_usage(FILE *to, const char *prog);
int  usage_with(FILE *err, const char *prog, const char *msg); // returns 2

#endif 