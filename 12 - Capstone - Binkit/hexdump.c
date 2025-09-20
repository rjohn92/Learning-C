#include <stdio.h>

int cmd_hexdump(int argc, char **argv) {
    FILE *fp = stdin;                // default: read from standard input
    unsigned long offset = 0;        // how many bytes we’ve printed so far
    unsigned char byte;              // one byte buffer
 
    // If a filename is provided (and not an option), open it.
    if (argc > 1 && argv[1][0] != '-') {
        fp = fopen(argv[1], "rb");
        if (!fp) { perror("fopen"); return 1; }
    } else if (argc < 1) {
        fprintf(stderr, "Usage: %s [file]\n", argv[0]);
        return 1;
    }

    // Read 1 byte at a time and print it in hex, 16 per line.
    while (fread(&byte, 1, 1, fp) == 1) {
        if (offset % 16 == 0) {
            // Print the starting offset for this row (8 hex digits)
            printf("%08lX: ", offset);
        }

        // Print the current byte as two hex digits
        printf("%02X ", byte);

        // Move to the next byte; if we've printed 16, end the line.
        offset++;
        if (offset % 16 == 0) {
            putchar('\n');
        }
    }

    // If we ended mid-row, print a final newline
    if (offset % 16 != 0) {
        putchar('\n');
    }

    if (fp != stdin) fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    return cmd_hexdump(argc, argv);
}