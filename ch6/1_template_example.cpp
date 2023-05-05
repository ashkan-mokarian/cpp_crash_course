/* 'Generic Programming'
* Writing a mean function. One way is to use function overloading for all the types
* long, float, int, etc. you have to copy-paste alot. maintenance hard. make code
* reusable by using templates.
*/
#include <cstdio>
#include <cstddef>

template <typename T>
T mean(const T* values, size_t length) {
    T result{};
    for(size_t i{}; i < length; i++) {
        result += values[i];
    }
    return result/length;
}

int main() {
    const double nums_d[] { 1.0, 2.0, 3.0, 4.0 };
    const auto res1 = mean<double>(nums_d, 4);
    printf("double: %f\n", res1);

    const float nums_f[] { 1.0f, 2.0f, 3.0f, 4.0f };
    const auto res2 = mean<float>(nums_f, 4);
    printf("float: %f\n", res2);

    const size_t nums_c[] { 1, 2, 3, 4 };
    const auto res3 = mean<size_t>(nums_c, 4);
    printf("size_t: %zd\n", res3);

    /* Automatic 'Template type deduction' whenever possible
    * Whenever the compiler can deduce the type, you can omit the template parameter
    * when using the template. This can lead to easier code maintainability
    */
    printf("\n=== with template type deduction ===\n");
    const double nums_dd[] { 1.0, 2.0, 3.0, 4.0 };
    const auto res4 = mean(nums_dd, 4);
    printf("double: %f\n", res4);

    const float nums_ff[] { 1.0f, 2.0f, 3.0f, 4.0f };
    const auto res5 = mean(nums_ff, 4);
    printf("float: %f\n", res5);

    const size_t nums_cc[] { 1, 2, 3, 4 };
    const auto res6 = mean(nums_cc, 4);
    printf("size_t: %zd\n", res6);
}