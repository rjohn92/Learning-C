#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct car { char *name; float price; int speed; };

bool car_equal(const struct car *a, const struct car *b) {
    // TODO: compare speed and price directly; compare names with strcmp (handle NULLs)
    const struct car *x = a;
    const struct car *y = b;

    if (!x || !y) {
        return false;
    }

    if (x-> price != y->price) {
        return false;
    }

    if (x-> speed != y->speed) {
        return false;
    }

    int result = strcmp(x->name, y->name);
    if (result != 0) {
        return false;
    }

    return true;
}

int main(void) {
    struct car w = {"Saturn", 16000.0f, 175};
    struct car x = {"Saturn", 16000.0f, 175};


    printf("equal? %s\n", car_equal(&w,&x) ? "yes" : "no");

    struct car y = {"Mustang", 33000.0f, 215};
    struct car z = {"Firebird", 65000.0f, 260};

    printf("equal? %s\n", car_equal(&y,&z) ? "yes" : "no");

}
