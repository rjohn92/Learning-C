#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};

int main(void) {
    struct car saturn;
    saturn.name = "Astra";
    saturn.price = 600.00;
    saturn.speed = 120;

    printf("Car name: %s\n", saturn.name);
    printf("Car price: $%.2f\n", saturn.price);
    printf("Car speed: %d km/h\n", saturn.speed);
}