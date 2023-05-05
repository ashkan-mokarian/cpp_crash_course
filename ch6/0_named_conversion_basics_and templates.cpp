/* Template
* Compile-time polymorphism in C++ is achieved by 'template's. A 'template' is
* a class or function with 'template parameter'. These parameters can stand in 
* for any type (primitive or user-defined). 'Template instantiation' is the process
* of creating a class or function from the template. 
* Why? The idea is to reuse code.
* How? 'template' prefix with <>. Inside diamonds goes 'template parameter' name
* by using one of the keywords 'typename' or 'class' (confusing but again because
* of historic reasons both are kept. use typename like the book).
*/

#include <cstdio>
#include <stdexcept>

// first define the 'template parameters', then you can use then inside of class
// or function as if they were actual 'type's
template <typename X, typename Y, typename Z>
struct MyTemplateClass {
    X foo(Y&);
private:
    Z* member;
};

template <typename X, typename Y, typename Z>
X my_template_function(Y& arg1, Z* arg2) {
    return 0;
}

// 'template instantiation'


/* Named Conversion Functions
* Not exactly templates, but similar behavior. You can cast types to other types.
*
* const_cast function: to remove the const type from a type. for 'template parameter'
* use the type you want to cast it to. as function parameter, use the variable
* that you want the cast removed.
*
* static_cast: used for implicit conversion, e.g. one int type to another? for
* example cant convert float* to char*. 
*
* reinterpret_cast: for conversions that are not well-defined. Here, the programmer
* has to check whether this conversion is correct ot not and compiler cannot help.
*/

// you can use const_cast to gain write access to a const objects.
void carbon_thaw(const int& encased_solo) {
    // encased_solo++;  // compile error. changing const variable.
    auto& hibernation_sick_solo = const_cast<int&>(encased_solo);
    hibernation_sick_solo++;
}

short increment_as_short(void* target) {
    auto as_short = static_cast<short*>(target);
    *as_short = *as_short + 1;
    return *as_short;
}

/* Narrow cast example with template using static_cast
* Let's write a template that checks for narrow cast using template.
* e.g. when casting an int to short, if int value is small enough to fit into short
* , the conversion is reversible and no narrowing occurs.
*/
template <typename To, typename From>
To narrow_cast(From value) {
    const auto converted = static_cast<To>(value);
    const auto backward = static_cast<From>(converted);
    if (value != backward) throw std::runtime_error("Narrowed!");
    return converted;
}

int main() {
    // static_cast example
    short beast{ 665 };
    auto beast_and_one = increment_as_short(&beast);
    printf("%d: beast + 1\n", beast_and_one);

    float on = 3.5166666;
    // auto not_alright = static_cast<char&>(&on);  // compile error
    // Because this conversion is not well-defined and static_cast cannot be used.
    // For this kind of shinanigens, you need **`reinterpret_cast`**

    // reinterpret_cast example
    // compiler doesn't know what type is located at memory address Ox1000 (memory
    // on an embedded device). with reinterpret_cast you as programmer can take 
    // full control.
    auto timer = reinterpret_cast<const unsigned long*>(0x1000);
    // printf("Timer is: %lu\n", *timer);  // This doesn't give compile error and 
    // build will finish successfully, but you'll get an EXC_BAD_ACCESS? point is
    // it runs.

    // Testing narrow_cast
    int perfect{ 496 };
    const auto perfect_short = narrow_cast<short>(perfect);
    printf("Narrowed int: %d to short: %hd\n", perfect, perfect_short);
    try {
        int cyclic{ 142857 };
        const auto cyclic_short = narrow_cast<short>(cyclic);
        printf("Narrowed int: %d to short: %hd\n", cyclic, cyclic_short);
    } catch(const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }

}