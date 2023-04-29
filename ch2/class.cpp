/*
* Classes are user defined types that has: *data member* and *member function*.
* It has also *access control*: Public, and private and protected.
* everyone can access public members, but only the class can access private.
* For structs, all members are public by default. However you can use private
* access control keyword in a struct to make it private.
*
* If `class` keyword is used instead of `struct`, the default access control for
* members become private. That's the only difference between struct and class.
* Therefore both can be used interchangebly. This book uses struct, but other
* conventions exists.
*/

#include <cstdio>
#include <cstdint>

class ClockOfTheLongNow {
    int year;

public:
    // Constructor
    ClockOfTheLongNow() {}
    ClockOfTheLongNow(int year_in) {
        year = 2019;
        if (!set_year(year_in)) {
            year = year_in;
        }
    }
    void add_year() {
        year++;
    }
    bool set_year(int new_year) {
        if (new_year < 2019) return false;
        year = new_year;
        return true;
    }
    int get_year() {return year;}
};

int main() {
    ClockOfTheLongNow clock;
    if (!clock.set_year(2018)) {
        clock.set_year(2019);
    }
    clock.add_year();
    printf("Year is: %d\n", clock.get_year());

    // Using constructor for object initialization.
    ClockOfTheLongNow anotherclock{ 2021 };
    printf("Year is: %d\n", anotherclock.get_year());

    struct PodStruct
    {
        uint64_t number;
        char string[256];
        bool valid;
    };

    // braced initialization is the way to go.
    PodStruct pod1{};
    printf("uninitialized struct: %llu\t%s\t%d\n", pod1.number, pod1.string, pod1.valid);
    PodStruct pod2{ 20, "Hello World", false};
    printf("--initialized struct: %llu\t%s\t%d\n", pod2.number, pod2.string, pod2.valid);
    
    // The order is important and can only be ommited from right to left.
    int arr1[5]{};  // [0, 0, 0, 0, 0]
    int arr2[]{ 1, 2, 3, 4, 5 };  // [1, 2, 3, 4, 5]
    int arr3[5]{ 1, 2, 3 };  // [1, 2, 3, 0, 0]
    int arr4[5];  // uninitialized values

    // Another reason why you should use 'braced initialization'.
    // with paranthesis, a function is called and may cause issues. for example
    // the 'nasty narrowing conversion.
    float a{ 1 };
    float b{ 2 };
    int narrowed_result(a/b);
    // int result{ a/b };  // if uncommented, compiler generates Warning.
    // So, always use braced initialization. much safer.

    /*
    * Destructors: they are optional. Sometimes is needed, e.g. releasing file
    * handles, flushing network sockets, freeing dynamic objects. If no destructor
    * is defined, nothing will be done at the object's end of life cycle.
    */
    struct Earth
    {
        ~Earth() {
            printf("Releasing space of earth for pass through!\n");
        }
    };
    {
        Earth my_earth;
    }

    return 0;
}