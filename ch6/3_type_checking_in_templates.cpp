/*
* Templates are type safe. During template instantiation, the compiler pastes in
* the template parameter. If the resulting code is incorrect -> compile error.
* But the compiler error message is very difficult to decipher. Because when the
* compiler instantiates a template, it pastes the template parameter, and tries
* to compile the code, and if there is an error, it only shouts as an instantiation
* error. Similar to duck-typed languages, e.g. Python. 
*
* 'Duck-typed' languages, defer type checking until runtime. The underlying 
* philosophy is that if an object looks like a duck, and quacks like a duck, then
* it must be of 'type' duck.
*
* Template programming in C++ shares similarity to these. Although templates might
* blow up at compile time and not at runtime.
*/
#include <cstdio>

template <typename T>
T square(T value) {
    return value * value;
}

int main() {
    char my_char{ 'Q' };
    auto result = square(&my_char);  // Bang!
}

/* SOLUTION
* 'concept' in C++ is the solution to this problem. The problem is somehow you
* defer checking until first use, and not at the time of instantiation.
*/