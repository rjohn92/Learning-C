#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// accept optional filename
int main(int argc, char *argv[]) {

    // If a filename is provided as an argument, use it; otherwise, use NULL for stdin
    const char *path = (argc > 1 ) ? argv[1]: NULL;
    
    if (path) {
    printf("The path is: %s\n", path);
    } else {
        printf("No path provided, using stdin\n");
    }
    
    // I'll get the flags here
    const char *bytes_flag = (argc > 2 && strcmp(argv[2],"-n")==0) ? argv[2]: NULL;
    if (bytes_flag) {
        printf("The bytes flag is: %s\n", bytes_flag);
    } else {
        printf("No bytes flag provided\n");
    }

    // get the nubmer of bytes to read
    const char *str_bytes = (bytes_flag && strcmp(bytes_flag,"-n")==0) ? argv[3]: NULL;
    uint64_t remaining = UINT64_MAX;  // treat as "no limit"

    if (str_bytes) {
        unsigned long long n = strtoull(str_bytes, NULL, 10);
        if (n == 0) {
            printf("Invalid number of bytes specified, defaulting to 16\n");
            remaining = 0;
        } else {
            remaining = (uint64_t)n;
            printf("The number of bytes to read is: %llu\n", n);
        }
    } else {
        printf("No number of bytes provided, defaulting to 16\n");
        str_bytes = "16"; // default to 16 bytes
    }
    
    // open file and read bytes
    FILE *fp = NULL;

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


    for(;;) {
        int byte = fgetc(fp);}

//     // Line Width for each row
//     const size_t width = 16;
//     unsigned char buf[16];
//     char ascii[16 + 1]; // +1 for '\0'

//     uint64_t offset = 0;

//     for (;;) {

//         // If we have a limit, then ask for the smaller of (width, remaining).

//         size_t want = width; 
//         if (remaining !=UINT64_MAX) {
//             if (remaining < want) {
//                 want = (size_t)remaining;
//             }
//         }

//         if (want == 0) {
//             break; // nothing more to read
//         }

//         size_t got = fread(buf, 1, want, fp);
//         if (got ==0) {
//             if (ferror(fp)) {
//                 perror("fread");
//             }
//             break; // EOF or error
//         }


//         printf("Offset %016llX: ", (unsigned long long)offset);

//         // Print hex bytes 
//         for (size_t i = 0; i < got; i++) {
//             printf("%02X ", buf[i]);
//         }

//         // now we pad the hex output if we read less than width
//         for (size_t i = got; i < width; i++) {
//             printf("   "); // 3 spaces for each missing byte
//         }

//         // Print ASCII representation
//         for (size_t i = 0; i < got; i++) {
//             unsigned char c = buf[i];
//             ascii[i] = (isprint(c)) ? c : '.';
//         }

//         ascii[got] = '\0'; // null-terminate the string

//         printf(" |%s|\n", ascii);

//         offset += got;

//         if (remaining == 0) {
//             break; // reached the limit
//         }


// }
//     if (fp != stdin) {
//         fclose(fp);
//     }
//     return 0;
// }




