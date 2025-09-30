#include <stdio.h>

// accept optional filename
int main(int argc, char *argv[]) {

    // If a filename is provided as an argument, use it; otherwise, use NULL for stdin
    const char *path = (argc > 1) ? argv[1]: NULL;
    FILE *fp = NULL;
    unsigned char buf[16];
    unsigned int offset = 0;

    // open file or use stdin
    if (path) {
        fp = fopen(path, "rb");
        if (!fp) {
            perror("fopen");
            return 1;
        }

    } else {
        fp = stdin;
    }

    unsigned int got = fread(buf, 1, sizeof buf, fp);
    while (got > 0) {
        printf("Offset %08X: ", offset);
        for (size_t i = 0; i < got; i++) {
            printf("%02X ", buf[i]);
        }
        printf("\n");

        offset += got;
        if (got < sizeof buf) {
            break;
        }
        got = fread(buf, 1, sizeof buf, fp);
    }

    if (fp != stdin) {
        fclose(fp);
    }
    return 0;
}




