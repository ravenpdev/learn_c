#include <stdio.h>

// typedef: Making New Types
// Basicall, you take an existing type and you make an alias for it with typedef.
//
// typedef and structs
struct animal {
    char *name;
    int leg_count;
    int speed;
};
typedef struct animal animal;

// This is the same as the previous example, just more concise.
typedef struct person {
    char *name;
    int age;
} person;

// Another common shortcut that you might see in code using what are called anonymous structures. It
// turns out you don't actually need to name the structure in a variety of places, and with typedef
// is one of them.
typedef struct {
    char *brand;
    int wheels_count;
    int door_count;
} car;

typedef struct {
    int x;
    int y;
} point;

int main(void) {
    {
        struct animal y; // This works
        animal z;        // This also works because "animal" is an alias
    }
}
