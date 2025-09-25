#include <stdio.h>

// accept optional filename
int main(int argc, char *argv[]) {
    char *path;
    FILE *fp = stdin;

    if (argc > 1 ) {
        path = argv[1];
    } else {
        perror("No file provided.\n");
        return 1;
    }

    if (path) {
        fp = fopen(path, "rb");
        if (!fp) {
            perror("Error opening file");
            return 1;
        } else {
            printf("File opened successfully.\n");
            return 0;
        }
    }




}



