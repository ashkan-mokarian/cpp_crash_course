/* Static Member:
* similar to static variables. defines a static member for a class which is
* allocated by the first object instantiation and can be used by any object of
* the class. However, it is initialized at the global scope by using class-access
* operator `::` outside of the class scope at global scope. Inside the class scope
* , it can be used without ::
*/
 
#include <cstdio>

struct RatThing {  // using struct to have default public members
    static int rat_things_power;  // static member
    static void power_up_rat_things(int nuclear_isotope) {  //static method so that we can invoke without object instantiation.
        rat_things_power = rat_things_power + nuclear_isotope;
        const auto waste_heat = rat_things_power * 20;
        if (waste_heat > 10000) {
            printf("Warning! Hot Doggie!\n");
        }
        printf("Rat-things power: %d\n", rat_things_power);
    }
};

int RatThing::rat_things_power = 200;  // initialized outside class scope, accessed via `::`

int main() {
    RatThing::power_up_rat_things(100);
    RatThing::power_up_rat_things(500);
}