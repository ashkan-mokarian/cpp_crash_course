/*
* 'Copy sematics': is "the meaning of copy" and programmers refer to the rules
* of making copies of objects. i.e. after x is copied into y, the rules are:
* 1. equivalence: x == y.
* 2. independence: changing x or y does not change the other.
*/
#include <cstdio>
#include <cstring>
#include <stdexcept>

int add_one_to(int x) {
    x++;
    return x;
}

struct Point {
    int x, y;
};
Point transpose(Point p) {  // gets a copy, and not the original one.
    auto tmp = p.y;
    p.y = p.x;
    p.x = tmp;
    return p;
}
// For primitive types and PODs this is straighforward. Both consist of a chunk
// of memory, and it is copied bit-by-bit to the other chunk of memory.

/* 'use after free' and 'double free'
* For classes, copying is tricky. members can have pointers that point to the
* same memory, and this causes nefarious bugs in code. For example, if one 
* destructs, and the other one is used, it generates unexpected behaviour.
* Apparently even worse, when the second one destructs, it becomes a mess and 
* possibly security issues.
* To overcome this we can use:
* - copy constructor: take care when using. Here you will copy all the object
*   to a new location in memory. imagine working with a large data. this is
*   inefficient unless you are sure you need a copy of the data. when possible,
*   use `const reference` instead.
* - 'Copy assignment': don't do the following:
*   `SimpleString a{ 50 };
*   `SimpleString b{ 50 };
*   `b = a;  // copy by assignment when you have not defined it yet. this uses
*            // the default copy behaviour unless defined for the class.
*   by using the `operator=` you can define an assignment operator. take note 
*   that it inherently creates a `this` shallow copy of the object and for the
*   'deepcopy', programmer needs to do the rest. Look at the copy assignment 
*   constructor for the SimpleString class.
*/

// Here we use the SimpleString class defined in 6_* to illustrate.
// Look for the 'Copy Constructor' in the class below.
class SimpleString {
    size_t max_size;
    char* buffer;
    size_t length;

public:
    SimpleString(size_t max_size)
        : max_size{ max_size },
        length{} {
            if (max_size == 0) {  // Because max_size is of type size_t, it is
                                  // unsigned by default and no need to check further.
                throw std::runtime_error{ "max_size must be at least 1." };
            }
            buffer = new char[max_size];
            buffer[0] = 0;
    }

    // Copy Constructor: a 'deep copy' of the object
    SimpleString(const SimpleString& other)  // const is used to not change the original
     :  max_size{ other.max_size },
        buffer{ new char[other.max_size] },  // use brace initialization and not =
        length{ other.length } {
        strncpy(buffer, other.buffer, max_size);
    }

    // Assignment operator overload: it always returns a reference to the class
    SimpleString& operator=(const SimpleString& other) {
        if (this == &other) return *this;  // This line is always like this. It is
          // good practice to check whether other referes to this.
        const auto new_buffer = new char[other.max_size];
        delete[] buffer;  // deallocate the memory created by the default assignment operator
        buffer = new_buffer;
        length = other.length;
        max_size = other.max_size;
        strncpy(buffer, other.buffer, max_size);
        return *this;  // This is always the same. always returns a reference to the result.
    }

    ~SimpleString() {
        delete[] buffer;
    }
    // (CADRe) Constructor Acquires, Destructor Releases: A design pattern where
    // memory is allocated in constructor and freed in desctructor to make sure
    // no memory leak happens.

    void print(const char* tag) const {
        printf("%s: %s", tag, buffer);
    }

    bool append_line(const char* x) {
        const auto x_len = strlen(x);
        if (length + x_len + 2 > max_size) return false;
        std::strncpy(buffer + length, x, max_size - length);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    }
};
void foo(SimpleString str) {
    str.append_line("We are changing it.\n");
}

int main() {
    int orignial = 1;
    auto result = add_one_to(orignial);
    printf("Original: %d, result: %d\n", orignial, result);
    // Here, original is unaffected because add_one_to gets a copy of it as its
    // argument. Passing by values. similar for user-defined POD.

    Point p;
    p.x = 1;
    p.y = 2;
    Point q = transpose(p);
    printf("Original: [%d, %d], result: [%d, %d]", p.x, p.y, q.x, q.y);

    printf("\n====== Copy Constructor ======\n");
    SimpleString a{ 50 };
    a.append_line("We apologize for ");
    SimpleString a_copy{ a };  // not using =, but instead copy constructor.
                               // This way, the copy is equivalent but independent
                               // from the original.
    a.append_line("inconvenience.");
    a_copy.append_line("incontinence.");
    a.print("a");
    a_copy.print("a_copy");

    printf("\n===== how cool, can now easily pass as argument by value =====\n");
    SimpleString empty_str{ 50 };
    foo(empty_str);
    empty_str.print("Still empty");

    printf("\n===== by copy assignment =====\n");
    SimpleString aa{ 50 };
    aa.append_line("We apologize for the");
    SimpleString bb{ 50 };
    bb.append_line(" last message.");
    aa.print("a");
    bb.print("b");
    bb = aa;  // copy assignment works as deepcopy!
    aa.print("a");
    bb.print("b");

}