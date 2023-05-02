/*
* Exceptions are *types* that communicate error conditions. When an error condition
* occurs, you 'throw' an exception. After throwing, now exception is 'in flight'.
* when exception is in flight, the program stops normal execution and searches
* for an exception handler. objects that fall out of scope during this are 
* destroyed.
* You need to handle errors. ways are:
* - error handling in constructors. 
* - checking error conditions and throwing exceptions
* - communicating error conditions with sending an error code, e.g. returning 
      error codes in functions.
*/

/*
* stdexcept includes header file for base exception classes in stdlib. has a 
* superclass except, where runtime_error, logic_error, and language support error
* (you won't use this directly. they indicate that some core language feature 
* failed at runtime) exceptions.
*
* logic_error: generally could be avoided through more careful programming. are
* used primarily when a class invariant can not be established (class invariant:
* a precondition for a class that compiler can not know about, and has to be
* enforced by the programmer). e.g. you use a class constructor to check for 
* various conditions, e.g. range of value, and if you cannot enforce a class
* invariant, you throw and exception.
*
* logic_error subclasses:
* - 'domain_error': valid input range e.g. sqrt(x)
* - 'invalid_argument': unexpected arguments
* - 'length_error': violate max size error
* - `out_of_range`: e.g. indexing a data structure
*
* runtime_error subclasses:
* - `system_error`: operating system got some error. e.g. timed_out, permission_
*     denied.
* - `overflow_error`, `underflow_error`: arithmetic errors.
*/
#include <stdexcept>
#include <cstdio>

struct Groucho
{
    void forget(int x) {
        if (x == 0xFACE) {
            // any object can be thrown, but use it with stdlib exception objects
            throw std::runtime_error("I'll be happy to throw an exception!\n");
        }
        printf("Forgot 0x%x\n", x);
    }
};

/* noexcept:
* a function modifier that communicates to compiler that this function does not
* throw an exception. used for performance optimization in special cases. but for
* now, I don't understand it. This noexcept identifier allows some code optimization
* to be used e.g. move (later on this).
*/
void hari_kari() noexcept {
    throw std::runtime_error{ "Goodbye, Cruel World!\n"};
}

/*
* use `try-catch` to establish exception handlers for a block of code. Within
* try block, put code that might throw an exception. in `catch`, specify handlers
* for each exception you can handle.
*/
int main() {
    // try-catch for noexcept function
    // but because hari_kari throws anyways, therefore C++ runtime will call the
    // function std::terminate, a function that by default will exit the program
    // via abort. However, this is just a showcase, but anyways, the compiler
    // is still liberated to use optimization e.g. move semantics, for this function
    // which may be faster.
    try {
        hari_kari();
    } catch(const std::exception& e) {
        printf("%s\n", e.what());
    }

    Groucho groucho;
    // try-catch howto
    try {
        groucho.forget(0xC0DE);
        groucho.forget(0xFACE);  // breaks the program's normal execution order
        groucho.forget(0xC0FFEE);  // this never gets executed.
    } catch(const std::runtime_error& e) {
        printf("Exception caught with message: %s.\n", e.what());
    }

    // catcher handles exception, if thrown is of the type or any subclasses of it
    try {
        throw std::logic_error{ "It's not about who wrong "
          "It's about who right"};
    } catch(const std::exception& e) {}
}
