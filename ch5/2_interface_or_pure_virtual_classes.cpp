/* Interface (pure virtual class) - and danger of not having virtual desctructors
* If all methods in a class are virtual, it is called a 'pure virtual class'.
* In C++, 'interface' are 'pure virtual classes'.
* Usually the also contain virtual destructors. O.w. prune to memory leak.
*/

#include <cstdio>

// Danger of not having virtual destructors
struct BadBaseClass {};
struct BadDerivedClass : BadBaseClass {
    BadDerivedClass() {
        printf("BadDerivedClass() invoked.\n");
    }
    ~BadDerivedClass() {
        printf("~BadDerivedClass() invoked.\n");
    }
};

// Good: with virtual destructor
struct BaseClass {
    virtual ~BaseClass() = default; // Why default? but default works, but not =0
};
struct DerivedClass : BaseClass {
    DerivedClass() {
        printf("DerivedClass() invoked.\n");
    }
    ~DerivedClass() override {
        printf("~DerivedClass() invoked.\n");
    }
};

int main() {
    printf("=== Memory leak: without virtual destructor ===\n");
    printf("Constructing BadDerivedClass.\n");
    BadBaseClass* bad{ new BadDerivedClass{} };
    printf("Deleting it as a BadBaseClass.\n");
    delete bad;

    printf("=== releasing memory correctly: with virtual destructor ===\n");
    printf("Constructing DerivedClass.\n");
    BaseClass* good{ new DerivedClass{} };
    printf("Deleting it as a BaseClass.\n");
    delete good;
}

/* TAKEAWAY
* To *declare* an 'interface', declare a 'pure virtual class'.
* To *implement* an 'interface', derive from it.
*
* Remember: the compiler cannot know ahead of time how much memory to allocate
* for the underlying type. Therefore you can only use references or pointes with
* interfaces. 'Consumer' uses interface via references or pointers to memory. To
* which memory is decided afterwards. Ways to achieve this:
* 1. 'Constructor injection': References cannot be reseated. in this approach you
*    use interface references and they don't change for the lifetime of the object.
*    usecase: when you want access to the same type of interface and not changing it.
*    Constructor is called once, and reference cannot be reseated.
* 2. 'Property injection': you use a method to set a 'pointer member'. This allows
*    to change the object to which the member points.
*    usecase: If you need the flexibility of modifying the field, by providing 
*    methods to perform property injection. methods can be called many times and
*    pointers can be reseated.
*/