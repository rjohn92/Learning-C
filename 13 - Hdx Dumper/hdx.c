#include <stdio.h>

// accept optional filename
int main(int argc, char *argv[]) {
    char *path;
    FILE *fp = stdin;

    if (argc > 1 && argv[1][0] != '-') {
        printf("File opened successfully.\n");
        fp = fopen(argv[1], "rb");
        if (!fp) {
            perror("fopen");
            return 1;
        }
        path = argv[1];
    } else {
        printf("No file provided.\n");
        return 1;
    }
        }



