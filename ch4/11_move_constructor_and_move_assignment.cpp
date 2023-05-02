/*
* Move constructor and assignment is similar to the copy version. just use 'rvalue'
* instead and compiler recognizes it accordingly. Just copy the data to the new
* object, and 0 out everything from the first one. This is important as it puts
* the first object into 'moved-from' state (if not done, pointer running free, etc.).
* 
* Executing this move constructor is *a lot* less expensive than copy constructor.
*
* IMPORTANT: remember that compilers love to run slow but very careful code.
* Therefore, your preference should be to use `noexcept` for move actions. The 
* move constructor is designed to not throw exceptions. Moreover, often compilers
* would choose a copy constructor instead of a exception throwing move constructor. Why is that? I don't get it.
*/

#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <utility>

// Same class as before, new part starts at the bottom of the class.
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

    // NEW STUFF ============================
    //
    SimpleString(SimpleString&& other) noexcept // rvalue reference to overload with noexcept
        : max_size{ other.max_size },
        buffer{ other.buffer },
        length{ length } {
        other.max_size = 0;
        other.buffer = nullptr;
        other.length = 0;
    }

    SimpleString& operator=(SimpleString&& other) noexcept {
        if(this == &other) return *this;  // This is the self assignment check. If the object is assigned to itself,
                                          // just return itself and don't waste computation. a = a;
        delete[] buffer;
        max_size = other.max_size;
        buffer = other.buffer;
        length = other.length;
        other.max_size = 0;  // putting other into 'move-from' state
        other.length = 0;
        other.buffer = nullptr;
        return *this;
    }
    
};

int main() {
    SimpleString a{ 50 };
    a.append_line("We apologize for");
    SimpleString b{ 50 };
    b.append_line("Last Message");
    a.print("a");
    b.print("b");
    b = std::move(a);  // here lvalue a is first changed to rvalue category type.
                       // hence move operator of SimpleString is called, and therefore
    a.print("a");      // a is in 'away-from' state.
    b.print("b");
}

/* RECAP:
* five methods govern move and copy behavior:
* - destructor
* - copy and move constructor
* - copy and move assignemtn operator
*
* If they are not defined explicitely, there are difficult rules to which are
* automatically defined and which not and depends sometimes on the compiler.
* Therefore, it's always good practice to explicitely define them, or use
* default or delete keywords.
*/