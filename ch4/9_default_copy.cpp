#include <cstdio>

// it is good practice to always assign `default` for the copy and assign operator.
// unless you don't want the default behaviour (which is shallow copy), and want
// to define it yourself.
struct Replicant {
    Replicant(const Replicant&) = default;
    Replicant& operator=(const Replicant&) = default;
};

// Some classes simply should not have 'copy constructor' or 'copy assignment operator'
// implemented. For example if the class manages a file or represents a mutual
// exclusive lock for concurrent programming. In this case, use the `delete`
// keyword to explicitly forbid the class.
struct Highlander
{
    Highlander(const Highlander&) = delete;
    Highlander& operator=(const Highlander&) = delete;
};

// any attempt to copy Highlander will lead to compiler error.
int main() {
    Highlander a;
    Highlander b{ a };
}

/* TAKEAWAY
* Always define the 'copy constructor' or 'copy assignment operator' explicitely
* especially if class deals with resources such as a network, file, printer, etc.
* in other cases, use `default` or `delete` keywords, but still explicitely
* define them to avoid nasty behaviour.
*/