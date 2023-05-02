#include <cstdio>

class Tracer {
public:
    // Constructor
    Tracer(const char* name): name{ name } {
        printf("%s constructed.\n", name);
    }
    // Destructor
    ~Tracer() {
        printf("%s desctructed.\n", name);
    }
private:
    const char* name;
};

static Tracer t1{ "Static variable" };
thread_local Tracer t2{ "thread_local variable" };

int main() {
    printf("A\n");
    Tracer t3{ "Automatic variable" };
    printf("B\n");
    auto* t4 = new Tracer{ "Dynamic variable" };
    printf("C\n");
}