#include "h.hpp"

int main(int, const char** argv)
{
    for (const auto& arg: Args(argv).args)
        print(arg);
}

