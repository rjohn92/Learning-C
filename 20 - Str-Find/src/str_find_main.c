#include "str_find_args.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct options opt = {0}; 
    int parse_rc = parse_args(argc, argv, &opt, stderr);
    if (parse_rc != 0) {
        return 2; 
    }