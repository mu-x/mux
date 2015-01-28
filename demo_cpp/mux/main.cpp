#include "threading.hpp"
#include <iostream>

class Counter
{
public:
    Counter(size_t count = 5)
        : _count(count)
        , thread(*this, &Counter::countDown)
    {}

private:
    void countDown()
    {
        while(_count)
            std::cout << _count-- << " ";
    }

    size_t _count;
    Thread thread;
};

int main()
{
    Counter a, b, c;
}
