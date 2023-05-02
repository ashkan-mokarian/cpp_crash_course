/*
* pyhton has garbage collector (automatic memory management). It periodically
* runs over the code and checks for garbage object. However, this causes overhead
* and performance issues.
* in c++, developer needs to know about object lifecycle:
* 1. storage/memory is 'allocated'
* 2. 'constructor' is called.
* 3. object's 'life time' begins.
* 4. object is available to use.
* 5. object's 'life time' ends.
* 6. 'destructor' is invoked.
* 7. memory 'deallocation'.
*/

/* Automatic Objects:
* 'automatic objects' is allocated at the beginning of enclosing code blocks and
* it's deallocated at the end. The enclosing block is an automatic object's
* 'scope'. Automatic objects are said to have 'Automatic Storage Duration'.
* Note that function parameters are automatic objects, even though notationally
* they appear outside of the function body, i.e. {}. They are also called
* 'local variables'.
*/

/* Static Storage Duration:
* by using `static` or `extern` keywords, objects can be defined at the
* 'global scope`. they are allocated when program starts and deallocated when
* program exits.
*
* `static`: has internal linkage. meaning it is accessible within the 'translation
* unit' of the source file it is defined in. 'Translation unit' is what is created
* by the 'preprocessor' acting on a single source file. (I think they are linked
* afterwards with a linker. but before the linker acts on the translation units,
* hence 'internal linkage')
* 
* 'extern': has external linkage. meaning that it is accessible within all the
* translation units created by the preprocessors acting on multiple source files.
* extern variables can be accessed by other translation units.
*
* 'local static': is a special kind of static variable that has a local scope
* rather than a global one. They are declared at function scope, just like
* automatic variables. But their lifetime begins at the first invokation of the
* enclosing function and ends when program exits.
*
* `thread-local` storage duration: a fundamental concept in concurrent programming
* is 'thread'. The sequence of instructions that a thread executes is called
* 'thread of execution'. special precautions need to be taken in consideration
* when writing code that uses multiple threads. it needs to be 'thread-safe'.
* Mutable global variables are a source of many thread safety issues.
* One way is to give each thread it's own copy of a variable. This can be done
* by using the `thread-local` keyword. Example:
* ```
* static thread-local int rat_things_power = 200;
* ```
* Now every thread has a local version initialized to 200. It is said that the 
* variable has 'thread-local storage duration'. Note: extern can be used instead
* of static which has corresponding modifications. Also, a thread-local variable
* is static implicitely and therefore the keyword static can be ommitted.
* This is covered in more detail later, just mentioning here for completeness.
*
* Dynamic Storage Duration:
* a 'dynamic object' or 'allocated object' is defined with the `new` keyword. 
* it is used on the rhs of `=` and the address of the dynamic object is used with
* pointer to work with the object. It's life cycle begins when the object is
* initialized and ends when it is deleted. To delete an object, use the `delete`
* keyword with the pointer. if you lose the pointer, then memory will be leaked.
* Note: depending on the compiler, the data of the object is not removed and hence
* dynamic objects can leak security issues. unless a destructor is used.
* IMPORTANT: with dynamic memory allocation comes flexibility but also responsibility.
* 'memory leaks' has to be taken care when using allocated objects. When writing
* user code, at least the OS kernel might clean up the leaked memories that were
* not deallocated by program, and free it up for reuse after program exits. But
* when writing low-level code, e.g. kernel code, the OS will not be able to do it
* and the memory becomes available only after system reboot.
*/

# include <cstdio>

// rat_things_power defined at global scope and has static storage duration.
static int rat_things_power = 200;
// or for external linkage, use extern.
extern int rat_things_power_extern = 200;
// bottom comment, does it appear in vscode variable hint? No, it doesn't. only
// the top comment does.

// nuclear_isotpe and waste_heat are local variables. they are allocated each
// the power_up_rat_thing is invoked, and deallocated just before function returns.
void power_up_rat_thing(int nuclear_isotope) {
    rat_things_power = rat_things_power + nuclear_isotope;
    rat_things_power_extern = rat_things_power_extern + nuclear_isotope;
    const auto waste_heat = rat_things_power * 20;
    const auto second_waste_heat = rat_things_power_extern * 20;
    if (waste_heat > 10000) {
        printf("Warning, Hot Doggie!\n");
    }
    if (second_waste_heat > 10000) {
        printf("Warning, Hot Doggie!\n");
    }
}

// local static version
void power_up_rat_thing_local_static(int nuclear_isotope) {
    // local static variables are only initialized when the first time the
    // function is invoked. The line below is not ran in the function calls afterwards.
    // check the last prints to see.
    static int rat_things_power_local_static = 200;
    rat_things_power_local_static = rat_things_power_local_static + nuclear_isotope;
    printf("Rat-things power local static after adding nuclear isotope: %d\n",
            rat_things_power_local_static);
    const auto waste_heat = rat_things_power_local_static * 20;
    if (waste_heat > 10000) {
        printf("Warning, Hot Doggie!\n");
    }
}

int main() {
    printf("Rat-things power: %d\n", rat_things_power);
    printf("Rat-things power extern: %d\n", rat_things_power_extern);
    power_up_rat_thing(100);
    printf("Rat-things power: %d\n", rat_things_power);
    printf("Rat-things power extern: %d\n", rat_things_power_extern);
    power_up_rat_thing(500);
    printf("Rat-things power: %d\n", rat_things_power);
    printf("Rat-things power extern: %d\n", rat_things_power_extern);

    printf("==================\n");
    //local static example
    power_up_rat_thing_local_static(100);
    power_up_rat_thing_local_static(500);
    // However, local static variables cannot be accessed outside the enclosing
    // function scope.
    // printf("%d\n", rat_things_power_local_static);  // compiler error.
    // This is a design patter called 'ENCAPSULATION'.

    // Dynamic or allocated objects
    int* ptr = new int;
    int* ptr_2 = new int{ 10 };
    printf("%d and %d are dynamic objects. Remember to delete them when not needed\n", *ptr, *ptr_2);
    delete ptr;
    delete ptr_2;
    // can also be used for dynamic arrays
    int* my_int_arr_ptr = new int[100];
    delete[] my_int_arr_ptr;  // but use array delete operator `delete[]`.

    // return 0; can be ommited apparently.
}