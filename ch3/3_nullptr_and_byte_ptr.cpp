#include <cstdio>
#include <cstddef>

int main() {
    // void* pointer is a C-syntax
    int a[] = { 1, 2, 3, 4, 5 };
    void* ptr = &a[2];
    // printf("%d\n", *ptr);
    // cannot derefence a void* pointer, because pointer to type is lost, and 
    // without the reference type, compiler cannot dereference.

    // however, it can have a special purpose. instead one can use nullptr.
    // implicitely, any value for a pointer that is not nullptr evaluates to 
    // true as a bool, and for nullptr to false. This is for example useful for
    // checking a return statement if it is valid, e.g. if memory could be allocated
    // or if not and with checking this, one can decide accordingly.
    int* ptr_2 = nullptr;
    if (!ptr_2) printf("we got a nullptr!\n");

    // For special usecases in low-level programming e.g. for reading and writing
    // files or working with sockets, we might need to point to bytes.
    std::byte byte_ptr;
    return 0;
}