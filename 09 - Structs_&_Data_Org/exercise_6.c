#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car { char *name; float price; int speed; };

struct car *new_car(const char *name, float price, int speed) {

    if (!name || !price || !speed) {
        printf("Invalid input!\n");
        return NULL;
    }

    struct car *c = malloc(sizeof(*c));  // allocate space for one car struct

    c->name = malloc(strlen(name) + 1); // allocate space for the name string
    
    if (c == NULL) {
        printf("Memory allocation failed!\n");
        free(c); // free previously allocated memory for struct
        return NULL;
    }



    strcpy(c->name, name);

    c->price = price;
    c->speed = speed;
    return c;
}


void free_car(struct car *c) {
    // TODO: free name first, then struct
}

struct car deep_copy(const struct car *src) {
    // TODO: return a by‑value copy with a NEW heap‑allocated name
}

int main(void) {
    struct car *a = new_car("Miata", 28000.0f, 205);
    struct car  b = deep_copy(a);

    b.name[0] = 'Y'; // mutate the copy's name

    printf("a.name=%s\n", a->name);
    printf("b.name=%s\n", b.name);

    free_car(a);
    free(b.name); // deep_copy allocated it
}
