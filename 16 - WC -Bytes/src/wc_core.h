#pragma once
#include <stdio.h>
#include <stddef.h>

int count_bytes(FILE *fp, size_t *out);
// static FILE* open_stream(const char *path);
int count_words(FILE *fp, size_t *out);
// void usage(const char *prog);
