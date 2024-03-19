#include "tank_control.h"

#define DEFAULT_CAPACITY 750

unsigned int capacity = 1000000;
unsigned int waste = 0;
unsigned int level = 0;
unsigned int capacity_bottle = DEFAULT_CAPACITY;

void clear() {
    level = 0;
    waste = 0;
}

void change_bottle_capacity(unsigned int c) {
    capacity_bottle = c;
}

void change_tank(unsigned int c) {
    capacity = c;
    if (level < capacity) return;
    waste += level - capacity;
    level = capacity;
}

void add(unsigned int c) {
    if (level + c > capacity) {
        waste += level + c - capacity;
        level = capacity;
    } else {
        level += c;
    }
}

unsigned int ship_out_bottles() {
    unsigned int bottles = level / capacity_bottle;
    level %= capacity_bottle;
    return bottles;
}

unsigned int get_wastes() {
    return waste;
}

unsigned int get_tank_level() {
    return level;
}