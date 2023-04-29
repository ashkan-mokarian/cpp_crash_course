/*
* To practice debugging in VSCode and gdb (GNU Debugger Tool - gcc), or LLDB 
* (low-level debugger - clang) in terminal. Note that programs compiled with
* GNU can use Clang debugger and vice versa.
*
* To enter GDB from terminal, compile this file using:
* `g++ stepfunc.cpp -o stepfunc -g`
* Then debug your program by writing `gdb stepfunc`. Use the following commands
* to interact with gdb:
* `break stepfunc.cpp:5` or `break main`
* `run`: to start running the debugger
* `step`: to step into
* `finish`: to step out
* `next`: to step over
* `info locals`: show local vars
* `continue`: to continue until next breakpoint
* `quit`: to exit gdb
*/
#include <cstdio>

int step_function(int x) {
    int result = 0;
    if (x < 0) result = -1;
    if (x > 0) result = 1;
    return result;
}

int main() {
    int num1 = 42;
    int result1 = step_function(num1);

    int num2 = 0;
    int result2 = step_function(num2);

    int num3 = -12345;
    int result3 = step_function(num3);

    printf("Num1: %d, Step: %d\n", num1, result1);
    printf("Num2: %d, Step: %d\n", num2, result2);
    printf("Num3: %d, Step: %d\n", num3, result3);

    return 0;
}
