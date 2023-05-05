/*
* 'Concepts' restrain template parameters, allowing for parameter checking at the
* time of instantiation, rather than first use of the parameter. This can lead
* to more friendly, informative error code--for example, "you tried to instantiate
* this template with char*, but this template requires a type that supports multiplication."
* Concepts allow to specify requirements on template parameters.
*
* A concept is a template. It's a constant expression involving template arguments,
* evaluated at compile time. It evaluates to true or false, for a given set of
* template parameters. If false, template instantiation fails and leads to compile
* error.
*
* How? same as 'template' but with `concept` keyword.
*/

/* 'type traits'
* the 'stdlib' library has utilities for inspecting type properties which are
* collectively called 'type traits'. Book says it is not out yet, so it could be
* different in new versions of -std=C++??
* as for now, they are in std <type_traits> header. examples are:
* is_void, is_integral, is_null_pointer, is_floating_point, is_enum, is_class,
* is_function, is_reference, is_same, and so on.
*/
#include <type_traits>
#include <cstdio>

constexpr const char* as_str(bool x) { return x ? "True" : "False"; }

int main() {
    printf("%s\n", as_str(std::is_integral<int>::value));
    printf("%s\n", as_str(std::is_integral<const int>::value));
    printf("%s\n", as_str(std::is_integral<char>::value));
    printf("%s\n", as_str(std::is_integral<uint64_t>::value));
    printf("%s\n", as_str(std::is_integral<int&>::value));
    printf("%s\n", as_str(std::is_integral<int*>::value));
    printf("%s\n", as_str(std::is_integral<float>::value));
}

/* NOTE
* However, these chcks are very limited. 'Type traits' tell you *what* the types
* are, but 'concepts' may require more flexibility. In 'concepts', you might check
* *how* the template will use them. For this you use 'requirements'.
*/