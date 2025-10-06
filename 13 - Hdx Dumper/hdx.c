#include <stdio.h>
#include <stdint.h>
#include <string.h>

// accept optional filename
int main(int argc, char *argv[]) {

    // If a filename is provided as an argument, use it; otherwise, use NULL for stdin
    const char *path = (argc > 1 ) ? argv[1]: NULL;
    printf("The path is: %s\n", path);
    // I'll get the flags here
    const char *bytes_flag = (argc > 2 && strcmp(argv[2],"n")) ? argv[2]: NULL;
    printf("The flag is: %s\n", bytes_flag);

    const char *bytes_to_read = (bytes_flag && strcmp(bytes_flag,"n")==0) ? argv[3]: NULL;
    if (bytes_to_read) {
        printf("The bytes to read is: %s\n", bytes_to_read);
    } else {
        printf("No bytes to read specified, defaulting to 16\n");
        bytes_to_read = "16";
    }

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
        char string_chunk[sizeof buf + 1] = {0}; // 16 chars + null terminator
        printf("Offset %08X: ", offset);
        for (size_t i = 0; i < got; i++) {
            printf("%02X ", buf[i]);
            if (buf[i] >= 0x20 && buf[i] <= 0x7E) {
                string_chunk[i] = buf[i];
            } else {
                string_chunk[i] = '.';
            }
        }

        
        printf(" |%s|\n", string_chunk);
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




