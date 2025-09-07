#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};

void discount_by_value(struct car c, float pct) {
    c.price *= (1.0f - pct); // modifies the copy only
}

void discount_by_ptr(struct car *c, float pct) {
    if (!c) {
        return;
    }
    c -> price *= (1.0f - pct);
}

int main() {
	// your code goes here
    struct car saturn = {
        .name = "Saturn Astra",
        .price = 3000.00,
        .speed = 150
        
    };
    
    printf("Saturn Astra Stats: Name: %s | Price: %.2f | Speed: %d\n", saturn.name, saturn.price, saturn.speed );
    
    discount_by_value(saturn, 0.5);
    printf("After discount by value: %.2f\n",saturn.price);
    
    discount_by_ptr(&saturn, 0.5);
    printf("After discount by pointer: %.2f\n", saturn.price);
    
    return 0;
    
}
