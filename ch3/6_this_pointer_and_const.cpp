/*
* Class members can be accessed by the 'this' literal. 'this' is a pointer to
* the object instance. However, it is implicitely used when using members, and 
* can be ommited. but sometimes, e.g. when function parameter and member have
* the same name, this-> can be used for clearnig the ambiguity.
*/

/*
* 'const' is a very powerful tool. makes sure that a class member or argument is
* not changed in it's scope. some use cases are: 1. const function arguments.
* const methods. etc.
*/

#include <cstdio>

class ClockOfLongNow
{
private:
    int hour{};

public:
    ClockOfLongNow(int hour) {
        this->hour = hour;
    }
    void set_hour(int hour) {  //e.g. a const here would raise compiler error.
        this->hour = hour;
    }
    // const methods: making a method const communicates that you promise to not
    // to modify the current object's state within the const method, ow. you get
    // a compiler error. put another way, these are READ-ONLY methods.
    int get_hour() const {
        return hour;
    }
    void show_hour() {
        printf("hour is: %d\n", hour);
    }
};

// see here, a const parameter is used, meaining that clock is read-only.
// therefore this object can not change inside this function. but in this function
// there is some function calls, that might change the state. Therefore, if any
// of this methods were not defined as *const method* it would have raised 
// compiler error.
bool is_outside_daily_hours(const ClockOfLongNow& clock) {
    if (clock.get_hour() > 23) return true;
    if (clock.get_hour() < 0) return true;
    return false;
}

// const argument: Defining a pointer or reference argument as const, makes sure
// that the object being passed to the function is not altered and is used only
// in READ-ONLY mode. noice!
void petruchio(const char* shrew) {
    printf("Fear not little wench, they shall not touch thee, %s.", shrew);
    // shrew[0] = 'K';  // uncomment to get compiler error for changing readonly variable.
}

// const member variable: cannot be changed after initialization.
struct Avout {
    const char* name = "Erasmum";
    ClockOfLongNow apert;
};

// IMPORTANT NOTATION: sometimes you want const member variables, but want to
// define them in a constructor via parameters, e.g. at runtime. To do this:
// a colon after the constructor parametrs similar to the example below is used.
class AvoutBetter {
    const char* name;
    ClockOfLongNow apert;
public:
    AvoutBetter(const char* name, int hour_of_apert)
    // 'Member initializer list': here, we have used a member initializer list
    // to brace initialize member variables before the constructor's body.
    // doing it outside the body has the advantages:
    // - members are intialized outside constructor's body, which leaves the body
    //   for important stuff and not deal with error checking.
    // - gives structure and members are initialized once.
      : name{ name }, apert{ hour_of_apert } {
    }
    void announce() const {
        printf("My name is %s and my next apert is at %d o'clock.\n", name, apert.get_hour());
    }
};

int main() {
    ClockOfLongNow clock{0};
    clock.set_hour(12);
    clock.show_hour();

    is_outside_daily_hours(clock);

    AvoutBetter jaz{ "Erasmus", 10 };
    AvoutBetter jad{ "Jad", 22 };
    jaz.announce();
    jad.announce();

    return 0;
}