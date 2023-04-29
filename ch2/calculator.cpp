#include <cstdio>

enum class Operation {
    Add,
    Sub,
    Mul,
    Div
};

class Calculator
{
private:
    Operation op;
public:
    Calculator(Operation op_input) {
        op = op_input;
    }
    int calculate(int a, int b) {
        switch (op)
        {
        case Operation::Add: {
            return a+b;
            printf("doing addition.");
        } break;
        case Operation::Sub:
            return a-b;
            break;
        case Operation::Mul:
            return a*b;
            break;
        case Operation::Div:
            return a/b;
            break;
        }
    }
};

int main() {
    Calculator calculator {Operation::Sub};
    printf("Result is: %d\n", calculator.calculate(10, 20));
    return 0;
}