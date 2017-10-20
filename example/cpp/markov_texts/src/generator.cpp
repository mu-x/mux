#include <iostream>
#include <markov_texts/dictionary.h>

int main(int, char** argv)
{
    try
    {
        if (!argv[1])
            throw std::invalid_argument("Start phrase is required");

        const auto start = markov_texts::parseSequence(argv[1]);
        int length = argv[2] ? std::stoi(argv[2]) : 10;
        if (length <= 0)
            throw std::invalid_argument("Wrong length paramiter");

        markov_texts::DictionaryGenerator generator;
        generator.load(stdin);
        generator.generate(start, stdout, static_cast<size_t>(length));
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}
