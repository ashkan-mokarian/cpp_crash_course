/*
* pointers & references are low-level types in c. There are usually better ways
* to do stuff in c++. pointers are dangerous and have several issues. 
* Nevertheless, they are fundamentals of C++. pointers point to memory and they
* carry the information needed to work with that chunk of memory, that is:
* 1. memory address 2. type of data in that memory.
*/

#include <cstdio>

int main() {
    int gettysburg{};
    printf("gettysburg: %d\n", gettysburg);
    int* gettysburg_address = &gettysburg;
    // %p literal for pointers
    printf("gettysburg_address: %p\n", gettysburg_address);

    // and use dereferencing to access the value at the memory.
    *gettysburg_address = 1500;
    printf("value @address:%p is: %d\n", gettysburg_address, *gettysburg_address);
    printf("also changes the original one: %d\n", gettysburg);

    class Clock {
        int hour{};
    
    public:
        void add_hour() {
            if (hour == 23) hour = -1;
            hour++;
        }
        int show_time() {
            printf("Times is %d:00\n", hour);
            return hour;
        }
    };

    // Member-of-pointer operator: ->
    Clock paris{};
    Clock* clock_ptr = &paris;
    clock_ptr->add_hour();
    clock_ptr->show_time();

    // the one in top is better, but if you are sick, you can also do this for dereferencing.
    (*clock_ptr).add_hour();
    (*clock_ptr).show_time();

    }