#include <cstddef>
#include <cstdio>

int main() {
    std::size_t size_c = sizeof(char);
    printf("Size of char: %zd\n", size_c);

    size_t size_i = sizeof(int); // can also be used without std::
    printf("Size of int: %zd\n", size_i);

    size_t size_si = sizeof(short int);
    printf("Size of short int: %zd\n", size_si);

    long int li = 1234L;
    size_t size_li = sizeof(li);
    printf("%ld is long int with size: %zd\n", li, size_li);

    unsigned long long int llui = 0xFFFFFFFFFF;
    size_t size_llui = sizeof(unsigned long long int);
    printf("%llu is unsigned long long int with size: %zd\n", llui, size_llui);

    float f = 3.14F;
    size_t size_f = sizeof(f);
    printf("%f is float with size: %zd\n", f, size_f);
    printf("%e in scientific format\n", f);
    printf("%g letting compiler choose best.\n", f); // recommended

    double d = 3.14;
    size_t size_d = sizeof(d);
    printf("%lf - or %lg is a double with size:%zd\n", d, d, size_d);

    long double Lf = 1.234e-10L; //don't know what the L does. when removed, does the same thing.
    size_t size_Lf = sizeof(Lf);
    printf("%Lg is a long double with size:%zd\n", Lf, size_Lf);

    bool t_b = true;
    bool f_b = !t_b;
    printf("TRUE || False == %d\n", t_b || f_b);
    size_t size_b = sizeof(bool);
    printf("size of bool is: %zd\n", size_b);

    // in order to run the code below. you need to add compiler flag -std=c++17.
    // to do it in VScode, change the task.json with adding flag in the args
    // section of tasks.json.
    std::byte var_byte;
    size_t size_byte = sizeof(var_byte);
    printf("size of a byte: %zd\n", size_byte);

    /*
    * can't define void type, although it is a built-in type.
    * void var; Compiler error.
    */

    // Arrays===================================================================
    int arr[10];
    size_t size_arr = sizeof(arr);
    printf("size of int array with 10 elements is:%zd\n", size_arr);

    // size of array can be inferred at compile time.
    int arr2[] = {10, 20, 30, 40};
    printf("infer size at compile time:%zd\n", sizeof(arr2));

    unsigned long maximum = 0; // can ommit the int type identifier as the compiler's
                           // default type is int
    unsigned long values[] = {10, 20, 30, 40, 0};

    for(size_t i=0; i < 5; i++) { // technically, size_t is correct but practically int works too
                                  // for example if size of array insanely large, size_t finds 
                                  // the best fit.
        if(values[i] > maximum) {
            maximum = values[i];
        }
    }
    printf("\nmaximum value in array is: %lu\n", maximum);

    // range-based for loop. compiler can infer length of array cuz it has a length.
    for(unsigned long value : values) {
        printf("%lu\t", value);
    }

    char english[] = "A book holds a house of gold.";
    char16_t chinese[] = u"\u4e66\u4e2d\u81ea\u6709\u9ec4\u91d1\u5c4b";
    printf("\n%s\n", english);
    printf("%s\n", chinese); // printing unicode to console is not this easy!

    return 0;
}