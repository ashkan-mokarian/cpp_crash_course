/*
* C++ as a stongly typed language, usually gets more than enough information for
* deducing types, and sometimes it's redundant. some cases are:
* - initialization with auto
* -
* -
*/

#include <cstdio>

int main() {
    int a{ 42 };  // this is redundant info
    
    // you can use `auto` instead.
    auto answer{ 42 };               // int
    auto foot{ 12L };                // long
    auto rootbeer{ 5.0F };           // float
    auto cheesburger{ 10.0 };        // double
    auto political_claims{ false };  // bool
    auto cheese{ "string" };         //char[7]
    // OK! so what? i get to save some time?
    // well, much better.
    // 1. sometimes for some libraries and not the primitive types, auto becomes handy.
    // 2. makes refactoring easier.

    // literals `const`, `*`, and `&` can also be used
    auto year{ 1401 };
    auto& year_ref = year;          // int&
    const auto& year_cref = year;   // const int&
    auto* year_ptr = &year;         // int*
    const auto* year_cptr = &year;  // const int*

    
    return 0;
}