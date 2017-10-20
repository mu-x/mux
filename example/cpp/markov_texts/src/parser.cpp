#include <iostream>
#include <markov_texts/dictionary.h>

int main(int, char** argv)
{
    try
    {
        int order = argv[1] ? std::stoi(argv[1]) : 1;
        if (order <= 0)
            throw std::invalid_argument("Wrong order paramiter");

        markov_texts::DictionaryBuilder dictionary;
        dictionary.parse(std::cin, static_cast<size_t>(order));
        dictionary.save(std::cout);
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}
