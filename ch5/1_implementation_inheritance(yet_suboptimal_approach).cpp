/* implementation inheritance
* Bad idea still existing. it is a bad practice from old c++. now better ways.
* it is an anti-pattern. child inherits from parent. etc. You might encounter
* it in legacy code. Also, because of history, implementing interfaces share
* lineage with inheritance. But interfaces are better ways of doing inheritance.
* but there is no interface keyword in C++. Unfortunately.
*/

/*
* Derived class inherits non private members of a base class. But over the years,
* programmers understood that member inheritance is problematic.
*/

#include <cstdio>

struct BaseClass
{
    int the_answer() const {return 42;}
    const char* member = "gold";
private:
const char* holistic_detective = "Dirk Gently";
};

struct DerivedClass : BaseClass {};

/*
* To inherit methods of a base class, one defines 'virtual' methods and the derived
* class implements the method using `override` keyword.
*/

/* 'pure virtual method'
* adding the suffix `=0` to a virtual method, makes them 'pure virual method'.
* A class can't inherit without implementing the pure virtual methods.
*/
struct BaseClass2
{
    virtual const char* final_message() const = 0;
};
struct DerivedClass2 : BaseClass2 {
    const char* final_message() const override {
        return "Sorry for the inconvenience";
    }
};
struct AnotherDerivedClass2 : BaseClass2 {
    const char* final_message() const override {
        return "Sorry for the incontenience";
    }
};


int main() {
    DerivedClass x;
    printf("Answer is: %d\n", x.the_answer());
    printf("%s memeber.\n", x.member);
    // This line gives compile error
    // printf("%s Holistic Detective Agency.\n", x.holistic_detective);

    // Class 2
    printf("======= Class 2 =============\n");
    // BaseClass2 base; This produces error, because it is an abstract class?
    DerivedClass2 derived;
    AnotherDerivedClass2 another_derived;
    BaseClass2& ref = derived;
    printf("DerivedClass2:            %s\n",derived.final_message());
    printf("AnotherDerivedClass2:     %s\n",another_derived.final_message());
    printf("BaseClass2& (to derived): %s\n",ref.final_message());
}

/* IMPORTANT
* Virtual functions incur runtime overhead (about 25% of the function, somehow
* typically low). The compiler generated 'vtables: virtual function tables'. 
* At runtime, the 'consumer' doesn't know the exact function, just knows how to
* use a function thanks to the 'vtable', which holds pointers to functions.
*/