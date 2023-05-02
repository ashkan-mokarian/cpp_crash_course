/* 'Call Stack':
* The 'call stack' is LIFO runtime structure that manages the function calls of
* a program. When a program (caller) invokes a function (callee), a new element
* is pushed into the call stack and this enables nested calls. an element is poped
* from top of the stack when the function is returned and control is given to the
* caller again.
*/

/* call stack and exceptions:
* When an exception is thrown, the runtime looks for an appropriate handler in 
* the current stack frame, if nothing is found, it pops the corresponding frame
* and unwind the 'call stack' until an appropriate 'exception handler' is found.
* Any objects whose lifetimes ends are destroyed in the usual way.
* To elaborate more on this, consider throwing an exception inside a destructor.
* Now consider where an exception is already 'in flight', and by unrolling the
* stack in search for a handler, and of course destroying any object whose lifetime
* ends, another exception is in flight. Now, how should the C++ runtime handle
* the two in flight exceptions. Juggling with chainsaws. Therefore if ever this
* was needed, the exception has to be handled inside the destructor itself, o.w.
* the runtime will call 'terminate'.
* IMPORTANT: As a general rule, treat destructors as if they were noexcept.
*/

#include <cstdio>
#include <stdexcept>

struct CyberdyneSeries800 {
    CyberdyneSeries800() {
        printf("I'm a friend of Sarah Conner!\n");
    }
    ~CyberdyneSeries800() {
        throw std::runtime_error{ "I'll be back.\n"};
    }
};

int main() {
    try {
        CyberdyneSeries800 t800;
        throw std::runtime_error{ "Come with me if you want to live.\n"};
    } catch(const std::exception& e) {
        printf("Caught exception: %s\n", e.what());
    }
}

// if you want to see the results of this code, go to terminal and compile it 
// yourself. you need the flag -O0
// clang++ -O0 -std=c++17 -o ./output/a.out ./ch4/5_callstack_and_exceptions.cpp
// after running, you see the program invokes std::terminate.