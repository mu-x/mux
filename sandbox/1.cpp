#include "1.h"

struct A
{
    A(int i): i(i) { PRINT("int i=" << i); }
    //A(const A& a): i(a.i) { PRINT("A i=" << i); }
    A(const A& a) = delete;

    int i;
};

int main()
{
    A a1 = 1;
    A a2{2};
    A a3(3);
}

