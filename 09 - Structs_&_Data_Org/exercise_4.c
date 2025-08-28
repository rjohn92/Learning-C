#include <stdio.h>

struct car { char *name; float price; int speed; };

int main(void) {

    // idk anything about cars tbh
    struct car inventory[] = {
        {"Bugatti", 406000.0f, 300},
        {"Honda Civic",       22000.0f, 190},
        {"Miata",       28000.0f, 205},
        {"Toyota Corolla",     21000.0f, 185},
        {"Saturn Astra",      3000.0f, 150},
        {"Ford Mustang",      26000.0f, 250},
        {"Chevrolet Camaro",  25000.0f, 240},
        {"Ferrari F8",  280000.0f, 340}
    };

    // number of cars in inventory
    size_t n = sizeof inventory / sizeof inventory[0];
    if (n == 0) {
    printf("No cars in inventory\n");
    return 1;   
    }
    int max_speed = 0; 
    float total_price = 0.0f;

    struct car fastest_car = inventory[0];



    for (size_t i = 0; i < n; i++) {
            total_price += inventory[i].price;
        if (inventory[i].speed > max_speed) {
            max_speed = inventory[i].speed;
            fastest_car = inventory[i];
        }

    }
    printf("The fastest car is %s with a speed of %d km/h\n", fastest_car.name, fastest_car.speed);
    printf("The average price of cars in inventory is $%.2f\n",total_price / n);
    return 0;
}
