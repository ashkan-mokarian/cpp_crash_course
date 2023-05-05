/* Variadic template
* Allowing arbitrary number of template paraters is done using 'variadic templates'
* instead of keyword `typename` you use `typename... Arguments` and Arguments is
* a replacement for zero or many template parameters.
*/

// Consider the example below, where in the SimpleUniquePointer class, we want 
// make a function that initializes the pointed to object with any arbitrary
// paramters, and not just the default initializor.

// here you declare the template paramters for the function make_simple_unique.
// the pointed-to object can be anything, possibly with arbitrary number of parameters.
// Therefore you use variadic template parameters to do so, and use them to 
// instantiate a pointed-to object.
template <typename T, typename... Arguments>
SimpleUniquePointer<T> make_simple_unique(Arguments... arguments) {
    return SimpleUniquePointer<T>{ new T{ arguments... } };
}


// NOTE: there is a better way of doing this using C++ stdlib