#include "h.hpp"

int main(int, const char** argv)
{
    for (const auto& arg: mux::Args(argv).args)
        mux::print(arg);
}

