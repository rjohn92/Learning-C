#include <stdio.h>

struct engine { int hp; float liters; };
struct car    { char *name; float price; int speed; struct engine eng; };

void tune(struct car *c, int add_hp) {
    // TODO: increase c->eng.hp by add_hp
    // TODO: bump c->speed by (add_hp/10)    
    if (!c) return; 

    c->eng.hp += add_hp;
    c->speed +=add_hp/10;
    
    

    
}

const struct engine *get_engine_const(const struct car *c) {
    // TODO: return pointer to embedded engine (const‑correct)
    if (!c) return NULL;
    return &c->eng;
}

int main(void) {
    struct car m = {.name="Miata", .price=28000, .speed=205, .eng={181, 2.0f}};
    printf("%s: %d hp, %d km/h\n", m.name, m.eng.hp, m.speed);
    tune(&m, 40);
    printf("%s: %d hp, %d km/h\n", m.name, m.eng.hp, m.speed);
}