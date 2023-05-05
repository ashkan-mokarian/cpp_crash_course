/* Simple 'unique pointer'
* A 'unique pointer' is an RAII (Resource Allocation Is Initializatio = CADRe)
* wrapper around a free-store-allocated object (? I think it means that we have
* allocated memory of an object but it doesn't have a name - it is an 'rvalue' -
* but we still have a 'pointer' pointing to it and we can also move the pointer.)
* But here, we don't leak memory, and because it is a RAII wrapper, then the 
* unique pointer's lifetime ends, the pointed-to object is destructed.
*
* The underlying type of the pointed-to object does not matter, hence making it
* a prime candidate for 'template's.
*/
#include <cstdio>
#include <utility>


// 'unique pointer' class as a RAII wrapper around a dynamically allocated object.
// It doesn't construct, bevause it has to be unique -> no 'double free' issues
// It can move and of course stay unique, without leaking memory. It is a 'move
// semantic' so it is efficient for large allocated resource. It only transfers
// ownership.
template <typename T>  // establishing a template type T as the type of the object being wrapped
                       // allowing it to be dynamically allocated without being 'lvalue'
struct SimpleUniquePointer {
    SimpleUniquePointer() = default;  // default constructor for null initialization.
                                      // default will be assigning pointer to `nullptr`
                                      // thanks to default intialization rules.
    SimpleUniquePointer(T* pointer)
        : pointer{ pointer } {
    }
    ~SimpleUniquePointer() {
        // we check if it is alreadt `nullptr` before deleting. I don't get it?
        // even if I delete without checking, getting same result?
        if(pointer) delete pointer;
    }
    // deleting default copy constructor and assignment, because it is a unique
    // pointer wrapper.
    SimpleUniquePointer(const SimpleUniquePointer&) = delete;
    SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;

    // Move constructor/operator is still valid. Here, this steals responsibility
    // of the object to the new owner. 
    SimpleUniquePointer(SimpleUniquePointer&& other) noexcept
        : pointer{ other.pointer } {
            other.pointer = nullptr;  // no need to delete, because 'move-from' 
              //object and will be destructed by compiler accordingly.
              // Once the move constructor returns, the moved-from object is destroyed.
    }
    SimpleUniquePointer&& operator=(SimpleUniquePointer& other) noexcept {
        if(pointer) delete pointer;  // for the case where pointer already pointnig to sth
          // and we need to deallocate it. You must *explicitely* check for prior 
          // ownership, because failure to delete a pointer leaks a resource.
          // This was not needed for move constructor, because move constructor
          // is only called when SimpleUni... is created. but in move assignment
          // it can happen during the lifecycle.
        pointer = other.pointer;
        other.pointer = nullptr;  // by setting this, first of all compiler auto
          // destructs the 'moved-from' pointer. second, it assures that if it's
          // lifetime ends, it doesn't destruct the wrapped around object.
        return *this;
    }

    T* get() {
        return pointer;
    }
private:
    T* pointer;
};

// We'll use the tracer to investigate the lifetime of the object
struct Tracer {
    Tracer(const char* name)
    : name{ name } {
        printf("%s constructed.\n", name);
    }
    ~Tracer() {
        printf("%s destructed.\n", name);
    }
private:
    const char* name;
};

void consumer(SimpleUniquePointer<Tracer> consumer_ptr) {
    printf("(consumer) consumer_ptr: %p\n", consumer_ptr.get());
}

int main() {
    // First, you dynamically allocate a Tracer. This prints the first message
    // from the Tracer constructor.You use the resulting Tracer pointer to construct
    // a simple unique pointer. 
    auto ptr_a = SimpleUniquePointer<Tracer>{ new Tracer("ptr_a") }; // isn't this the move constructor that we set to `delete`???
    // here you use the get method of the unique pointer to access the Tracer object's address.
    printf("(main)     ptr_a: 0x%p\n", ptr_a.get());
    // here you use std::move() to relinquish the Tracer of ptr_a to the consumer function.
    // now the lifecycle of the original Tracer object transfers to the enclosing 
    // consumer function. Hence ptr_a is moved-from and can die.
    consumer(std::move(ptr_a));  // now consumer_ptr owns Tracer. It shows the same
      // address as before, because it is pointing to the same object.
    // when consumer returns, consumer_ptr dies because its storage duration is 
    // the scope of consumer.

    // ptr_a is in moved-from state and holds now `nullptr`
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
    
}

// This is a simple implementation of stdlib's std::unique_ptr, which is a member
// of the family of RAII templates called 'smart pointers'.