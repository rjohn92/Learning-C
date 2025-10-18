// hexdump.c (single-file refactor)
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

enum { LINE_WIDTH = 16 };

static uint64_t parse_bytes(const char *str) {
    if (!str || !*str) {
        fprintf(stderr, "Missing value for -n! Defaulting to reading entire file.\n");

    }
    errno = 0;
    char *end = NULL;
    unsigned long long v = strtoull(str, &end, 10);

    // full-string numeric check
    if (end == str || *end != '\0') {
        fprintf(stderr, "Invalid -n value: '%s'! Defaulting to reading entire file.\n", str);

    }
    if (errno == ERANGE) {
        fprintf(stderr, "Value out of range for -n: '%s'\n", str);
    }
    return (uint64_t)v;
}

static FILE* open_stream(const char *path) {
    if (path == NULL) return stdin;
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return fp;
}

static void print_line(uint64_t offset, const unsigned char *buf, size_t got) {
    // Offset
    printf("Offset %016" PRIx64 ": ", offset);

    // Hex bytes
    for (size_t i = 0; i < got; i++) {
        printf("%02X ", buf[i]);
    }
    // pad if short read
    for (size_t i = got; i < LINE_WIDTH; i++) {
        printf("   ");
    }

    // ASCII
    putchar(' ');
    putchar('|');
    for (size_t i = 0; i < got; i++) {
        unsigned char c = buf[i];
        putchar(isprint(c) ? (char)c : '.');
    }
    // pad ASCII column too, so right border lines up
    for (size_t i = got; i < LINE_WIDTH; i++) {
        putchar(' ');
    }
    putchar('|');
    putchar('\n');
}

static void read_and_dump(FILE *fp, uint64_t limit /* UINT64_MAX = no limit */) {
    unsigned char buf[LINE_WIDTH];
    uint64_t offset = 0;

    for (;;) {
        if (limit == 0) break;

        size_t want = LINE_WIDTH;
        if (limit != UINT64_MAX && limit < want) {
            want = (size_t)limit;
        }

        size_t got = fread(buf, 1, want, fp);
        if (got == 0) {
            if (ferror(fp)) perror("fread");
            break; // EOF or error
        }

        print_line(offset, buf, got);
        offset += got;

        if (limit != UINT64_MAX) {
            limit -= got;
            if (limit == 0) break;
        }
    }
}

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s [path] [-n BYTES]\n", prog);
    fprintf(stderr, "  path      optional file path (stdin if omitted)\n");
    fprintf(stderr, "  -n BYTES  limit output to BYTES read (decimal)\n");
}

int main(int argc, char **argv) {
    const char *path = NULL;
    uint64_t limit = UINT64_MAX;

    // Simple argv scan: [path] is optional and must not start with '-'
    // Optional: "-n <num>"
    int i = 1;
    if (i < argc && argv[i][0] != '-') {
        path = argv[i++];
    }
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc) {
                usage(argv[0]); 
                exit(EXIT_FAILURE); 
            }
            limit = parse_bytes(argv[i+1]);
            i += 2;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage(argv[0]); return 0;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            usage(argv[0]); exit(EXIT_FAILURE);
        }
    }

    FILE *fp = open_stream(path);
    read_and_dump(fp, limit);
    if (fp != stdin) fclose(fp);
    return 0;
}
