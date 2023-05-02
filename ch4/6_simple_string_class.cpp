/*
* A simple string class that adds C-style strings and prints them.
* How to gel together constructor, desctructors, members, and exceptions.
*/
#include <cstdio>
#include <stdexcept>
#include <cstring>

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

class SimpleStringOwner {
private:
    SimpleString string;
public:
    SimpleStringOwner(const char* x)
    : string{ 10 } {  // members are constructed already by member initializer 
                      // once the enclosing constructor executes. o/w how can
                      // the constructor use it.
        if (!string.append_line(x)) {
            throw std::runtime_error{ "Not enough memory!" };
        }
        string.print("Constructed");
    }
    ~SimpleStringOwner() {  // the reverse happens for the enclosing destructor.
                            // first desctructor executes and in the end, the 
                            // member's destructor.
        string.print("About to destroy");
    }
};

void fn_c() {
    SimpleStringOwner c{ "cccccccccc"};
}
void fn_b() {
    SimpleStringOwner b{ "b" };
    fn_c();
}

int main() {
    SimpleString string{ 115 };
    string.append_line("Starbuck! Whadya hear?");
    string.append_line("Nothin' but the rain.");
    string.print("A");
    string.append_line("Grab your gun and bring the cat in.");
    string.append_line("Aye-aye sir, coming home.");
    string.print("B");
    if (!string.append_line("Galactica!")) {
        printf("String was not long enough to append another message.");
    }

    printf("\n========== SimpleStringOwner class =============\n");
    SimpleStringOwner x{ "x" };
    printf("x is Alive!\n");

    printf("\n========== call stack unwinding =============\n");
    try {
        SimpleStringOwner a{ "a" };
        fn_b();
        SimpleStringOwner d{ "d" };  // never gets called.
    } catch(const std::exception& e) {
        printf("Exception: %s\n", e.what());
    }

}

/* TAKEAWAY:
* "use of exception handling leads to programs that are faster when they execute
* normally, and better behaved when they fail."
* When a C++ program executes normally (no exceptions thrown), there is no runtime
* overhead associated with checking exceptions. It is only when an exception is
* thrown that you pay overhead. But here you get robustness and maintainablity instead.
*/