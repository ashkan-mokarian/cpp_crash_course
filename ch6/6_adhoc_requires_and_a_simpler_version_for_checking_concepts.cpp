/*
* I couldn't make ch6/5_... work. This is a simpler version.
* Also attaching requires to the template definition -> 'Adhoc concept'
*/

#include <stdexcept>
#include <type_traits>

template <typename T>
    requires std::is_copy_constructible<T>::value
T get_copy(T* pointer) {
    if (!pointer) throw std::runtime_error{ "Null-pointer dereference" };
    return pointer;
}

struct Highlander {
    Highlander() = default;
    Highlander(const Highlander&) = delete;
};

int main() {
    Highlander connor;
    auto connor_ptr = &connor;
    auto connor_copy = get_copy(connor_ptr);
}

// This should give compile error, but friendly, informative error code.