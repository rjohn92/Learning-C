#include <stdio.h>
static void copy_all(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (putchar(c) == EOF) {
            perror("stdout");
            return; // Exit on write error
        }
    }
    if (ferror(fp)) {
        perror("fgetc");
        return; // Exit on read error
    }
    return; // Success
}

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) {
        perror("hello.txt"); // Print error if file cannot be opened
        return 1; // placeholder
    }

    copy_all(fp);

    // Optional: check ferror(fp) and perror if needed
    fclose(fp);
    return 0;
}