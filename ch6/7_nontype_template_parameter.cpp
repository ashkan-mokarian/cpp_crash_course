/* Non-type template parameter
* The typical template parameter using `typename` was a representative for a type.
* By using non-type template parameter, one can use for example a value in order
* to achieve compile-time genericity.
*/

#include <stdexcept>
#include <cstdio>


// This is your typical generic function using template. But the length of the
// array (10) that we check is not generic. 
template <typename T>
T& get(T (&arr)[10], size_t index) {  // has an reference array as parameter, but
  // we have to specify the length and check for out-of-range, lacking genericity.
    if (index > 10) throw std::out_of_range("Out of Bounds.");
    return arr[index];
}

template <size_t Index, typename T, size_t Length>  // We can define non-type 
  // template parameters as shown here, if we wish to hardcode index and length to 
  // the implementation.
T& get(T (&arr)[Length]) {
    static_assert(Index < Length, "Out-of-bounds access.");  // static_assert is
      // a compile version of template parameter checking (maybe in newer C++ standards
      // this is done using concepts and requires). Anyhow, it check for a condition
      // on template parameters at compile time and outputs a informatice message
      // otherwise.
    return arr[Index];
}

int main() {
    int fib[]{ 1, 1, 2, 0 };
    // here the first one specifies all the template parameters explicitely,
    // and for the other two it is done implicitely.
    printf("%d %d %d ", get<0, int, 4>(fib), get<1>(fib), get<2>(fib)); 
    get<3>(fib) = get<1>(fib) + get<2>(fib);
    printf("%d ", get<3>(fib));
    // printf("%d", get<4>(fib));  // Bang!
}