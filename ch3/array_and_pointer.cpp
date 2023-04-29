#include <cstdio>

struct College
{
    char name[256];
};

void print_college(College* college_ptr) {
    printf("%s College\n", college_ptr->name);
}

void print_college_better(College* college_ptr, size_t n_colleges) {
    for (size_t i = 0; i < n_colleges; i++) {
        printf("%s College\n", college_ptr[i].name);
    }
}

int main() {
    College best_colleges[] { "tokhchi", "goozabad", "nabood_dge"};
    print_college(best_colleges);
    // this one should print all
    print_college_better(best_colleges, sizeof(best_colleges) / sizeof(College));

    // different ways of accessing arrays by pointers
    College* third_college_ptr = &best_colleges[2];
    College* third_college_ptr_2 = best_colleges + 2;
    printf("%s == %s\n", third_college_ptr->name, third_college_ptr_2->name);
    // one of the benefits of pointer-array arithmetic is:
    // gives you access to memory for low-level programming without any overhead
    // for example with embedded controllers.
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char* upper_ptr = &upper[0];

    lower[3] = 'd';
    upper_ptr[3] = 'D';
    // but if you are not careful, and forget the bounds, unexpected behavior
    // can arise. Compiler doesn't help here to debug and compiles w/o issues.
    lower[7] = 'g';
    printf("unexpected letter: %c\n", lower[7]);

    return 0;
}