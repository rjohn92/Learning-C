#include <stdio.h>
#include <stdlib.h>

struct car { char *name; float price; int speed; };

int cmp_price_asc(const void *p, const void *q) {
    const struct car *a = p, *b = q;
    return (a->price > b->price) - (a->price < b->price);
}

int cmp_speed_desc(const void *p, const void *q) {
    const struct car *a = p;
    const struct car *b = q;

    if (a -> speed < b -> speed) {
        return -1;
    }
    else if (b -> speed > b -> speed) {
        return 1;
    }
    else {
        return 0;
    }
}

static void print_all(const struct car *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%-10s $%7.2f %3d km/h\n", a[i].name, a[i].price, a[i].speed);
}

int main(void) {
    struct car inv[] = {
        {"Saturn",6000,175},
        {"Civic Si",32000.00,190},
        {"Miata",28000.00,205},
        {"Corolla",21000,185}
    };
    size_t n = sizeof inv/sizeof inv[0];

    qsort(inv, n, sizeof inv[0], cmp_price_asc);
    puts("By price asc:"); print_all(inv, n);

    qsort(inv, n, sizeof inv[0], cmp_speed_desc);
    puts("\nBy speed desc:"); print_all(inv, n);
}
