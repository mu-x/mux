#include "h.hpp"

using Data = mux::Traceble<int>;

struct S
{
    Data d;
    Data getD() { return d; }
};

void f(const Data& d)
{
    d.print();
}

int main(int, const char** argv)
{
    S s;
    s.getD().print();
    f(s.getD());
}

