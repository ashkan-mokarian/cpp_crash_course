/*
* References are safer than pointes. they cannot be assigned nullptr (easily).
* and they cannot be reseated(reassigned).
* they are declared by appending & operator to type name. they do not use 
* member-to-pointer notation not can they be dereferenced. much cleaner this way.
*/
#include <cstdio>

class ClockOfLongNow
{
    int hour{};
public:
    void set_hour(int h) {
        hour = h;
    }
    int get_hour() {
        return hour;
    }
    void show_hour() {
        printf("hour is: %d\n", hour);
    }
};

void add_year(ClockOfLongNow& clock) {
    clock.set_hour(clock.get_hour() + 1);
}

int main() {
    ClockOfLongNow clock;
    clock.set_hour(12);
    add_year(clock);  // note that no & is used. references are easy to deal with.
    clock.show_hour();

    return 0;
}
/*
* IMPORTANT: when to use references, and when pointers?
* pointers and references are to a large extend interchangable, and should almost
* always prefer references over pointers.
* However, in some use cases, that is if you have to assign nullptr to them, or
* the memory that they refer to needs to be changed, then pointers are used.
* Rememeber, references. cannot be assigned nullptr, and not reseated.
*/