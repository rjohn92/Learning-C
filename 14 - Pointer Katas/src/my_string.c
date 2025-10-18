# include <stdio.h>


size_t my_strlen(const char *s) {
    
    // printf("Calculating length of string: %s\n", s);
    const char *p = s;
    // printf("Pointer starts at address: %p\n", (void*)p);
    size_t length = 0;
    while (*p != '\0') {
        p++;
        length++;
        // printf("Pointer moved to address: %p | current length: %zu\n", (void*)p, length);
        // printf("Current character: '%c'\n", *(p-1));
    }
    return length;
}

char my_strchr (const char *s, int ch) {
    const char *p = s;
    while (*p != '\0') {
        if (*p == (char)ch) {
            printf("Found character '%c' at index %ld\n", ch, p - s);  
            return (char)*p;
        }
        p++;
    }
    return '\0';

}

int my_strcmp(const char *a, const char *b) {
    const unsigned char *p1 = (const unsigned char *)a;
    const unsigned char *p2 = (const unsigned char *)b;

    for (;;) {
        if (*p1 != *p2) {
            if (*p1 < *p2) {
                return -1;
        }
            else {
                return 1;
            }
        }
        if (*p1 == '\0' || *p2 == '\0') {
            break;
        }
        p1++;
        p2++;
    }

    return 0;
}


int main() {
    const char *test = "Hello, World!\0";
    const char *same_test = "";
    const char *diff_test = "Hello, Earth!\0";
    printf("Length of '%s' is %zu\n", test, my_strlen(test));
    
    printf("Character found: %c\n", my_strchr(test, 'X'));

    printf("Are same?: %d\n", my_strcmp(test, same_test));
    printf("Are same?: %d\n", my_strcmp(test, diff_test));


    return 0;
}
