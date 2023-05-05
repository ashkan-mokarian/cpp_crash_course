// IMPORTANT: this is not std=c++17. instead use -std=c++20. and the notation for
// concepts is slightly different from what the book says. Here is the correct version
// implemented.

/* Requires
* `requires` is a framework in C++ used by concepts to check for template arguments.
* It consists of expressions inside {} which should result in the type specified
* after -> . If all satisfied and valied and match the requirements, then the whole
* requires evaluates to true and the types are valid. If one fails, then results
* to false. Since these are checks done at compile time, no overhead at runtime 
* is counted toward performance, and hence concepts can contain any number of
* requires statements.
*/
#include <concepts>  // needed for keyword `concept`
#include <cstddef>
#include <cstdio>
#include <type_traits>

/*
* You can see that template T needs to satisfy three requirments.
* 1. T must be 'default constructible'.
* 2. T supports += operator.
* 3. Dividing T by size_t yields a T.
*/

// building a concept
template <typename T>
concept Averagable =  std::is_default_constructible_v<T>
    && requires (T a, T b) {  // define as many parameters as you need for checks.
        { a += b } -> std::same_as<T>;
        { a / size_t{ 1 }} -> std::same_as<T>;  // requires fields can have any subset of the parameters
    };


// Using a concept to check for a template definition.
// It's simple, just use the concept name, instead of the `typename` keyword.
template <Averagable T>
T mean(T* values, size_t length) {
    T result{};
    for(size_t i{}; i<length; i++) result += values[i];
    return result/length;
}

int main() {
  double nums_d[] { 1.0f, 2.0f, 3.0f, 4.0f };
  const auto result1 = mean(nums_d, 4);
  printf("double: %f\n", result1);
  float nums_f[] { 1.0, 2.0, 3.0, 4.0 };
  const auto result2 = mean(nums_f, 4);
  printf("float: %f\n", result2);
  size_t nums_c[] { 1, 2, 3, 4 };
  const auto result3 = mean(nums_c, 4);
  printf("size_t: %zu\n", result3);
}