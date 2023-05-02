/*
* Copying large data at runtime is not desirable. Instead, one can transfer 
* ownership to an new object without copying the data. This is not just simply
* renaming, because objects can have different lifetimes. When an object y
* is moved into x, y is in a special state called 'moved-from' state. You can
* only perform two operations on moved-from objects, 1. (re)assign them or 
* 2. destruct them. similar to copying, you move objects with defining move
* constructors or move operators.
*/
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <utility>  // used for std::move

// We'll use the SimpleString class again.
class SimpleString {
    size_t max_size;
    char* buffer;
    size_t length;

public:
    SimpleString(size_t max_size):
        max_size{ max_size },
        length{} {
            if( max_size == 0) {
                throw std::runtime_error("max_size has to be greater than zero.");
            }
            buffer = new char[max_size];
            buffer[0] = 0;
    }

    void print(const char* tag) const {
        printf("%s: %s", tag, buffer);
    }

    bool append_line(const char* x) {
        const auto x_len = strlen(x);
        if(length + x_len + 2 > max_size) return false;
        std::strncpy(buffer + length, x, max_size - length);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    } 
};

/* Value categories:
* There are many value categories in c++ which can be very confusing.
* For now let's only learn a simple version and what is useful. 'lvalue' and
* 'rvalue'. 'lvlaue' is any value that has a name, 'rvalue' is anyhting that is
* not lvalue.
* You can communicate to the compiler that a function accepts lvalues or rvalues
* using 'lvalue reference' and 'rvalue reference's. Until now, every functio
* reference parameter has been an lvalue reference. you can define rvalue reference
* by using &&.
* You can define same function name but with different parameter value categories
* and the compiler decides correctly.
*/

void ref_type(int &x) {  // lvalue reference
    printf("lvalue reference: %d\n", x);
}
void ref_type(int &&x) {  // rvalue reference
    printf("rvalue reference: %d\n", x);
}

int main() {
    SimpleString a{ 50 };
    SimpleString b{ a };  // a is a 'lvalue'
    SimpleString c{ SimpleString{ 50 } };  //   SimpleString{ 50 } is a 'rvalue'

    printf("================\n");
    auto x = 1;
    ref_type(x);  // lvalue reference
    ref_type(2);  // rvalue reference
    ref_type(x + 2);  // rvalue reference, because x + 2 is not bound to a name

    /*
    * You can use std::move to cast an lvalue reference to an rvalue reference
    */
   ref_type(std::move(x));  // this prints rvalue reference
}

/*
* So what is all this? Compiler has a safeguard for 'lvalue' stuff.
* TAKEAWAY: if an 'lvalue' is at hand, moving is suppressed. if an 'rvalue' is at
* hand, moving is enabled.
*/