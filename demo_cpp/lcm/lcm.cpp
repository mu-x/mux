#include "calculator.hpp"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

/** Usage: ./lcm [THREAD_COUNT] */
int main(int argc, char** argv)
{
    size_t threadCount = (argc > 1) ?
        static_cast<size_t>(atoi(argv[1])) : // comand line arg or
        static_cast<size_t>(sysconf(_SC_NPROCESSORS_ONLN)); // max system cores

    try
    {
        lcm::Calculator calc(threadCount);
        std::string line;
        while (std::getline(std::cin, line))
            calc.push(strtoull(line.c_str(), 0, 0));

        lcm::Multiples mults = calc.finalize();
        for (lcm::Multiples::const_iterator it = mults.begin();
                it != mults.end(); ++it)
            std::cout << it->first << "^" << it->second << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}
