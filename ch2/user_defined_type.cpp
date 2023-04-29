/*
* User defined types are: Enumeration, Class, Union.
*/
#include <cstdio>

enum class Race {
    Elf,
    Human,
    Dwarf,
    Lizard,
    Orc,
};

// Book calls these POD class(Plain Old Data classes). Good Rule of thumb, define
// members from largest to smallest
struct Book {
    char name[256];
    int year;
    int n_pages;
    bool hardcover;
};

int main() {
    Race enemy = Race::Human;

    switch(enemy) {
        case Race::Elf: {
            printf("Enemy is elf.");
        } break;
        case Race::Human: {
            printf("Enemy is human.");
        } break;
        case Race::Dwarf: {
            printf("Enemy is dward.");
        } break;
        default: {
            printf("Invalid enemy race.");
        }
    }

    Book neuromancer;
    neuromancer.n_pages = 888;
    printf("\nNeuromancer has %d pages\n", neuromancer.n_pages);

    // Unions: allocates memory to be able to hold any of the defined variables
    // inside. Therefore will allocate the largest one.
    // Note: it is very unsafe and should be avoided
    union Variant
    {
        char string[10];
        int integer;
        double floating_point;
    };
    
    Variant v;
    v.integer = 10;
    printf("integer is: %d\n", v.integer);
    v.floating_point = 3.1415;
    printf("double member is: %g\n", v.floating_point);
    // This is the problem with Unions.
    printf("integer is: %d\n", v.integer);
    // compiler doesn't help here. you have to make sure to use the correct
    // literal yourself.



    return 0;
}