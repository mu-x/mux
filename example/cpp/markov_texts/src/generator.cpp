#include <iostream>
#include <markov_texts/dictionary.h>

int main(int, char** argv)
{
    ++argv; // Binary;
    try
    {
        markov_texts::WordStream debugStream(stderr);
        if (*argv && *argv == std::string("--verbose"))
        {
            markov_texts::setDebugStream(&debugStream);
            ++argv;
        }

        if (!*argv)
            throw std::invalid_argument("Start phrase is required");

        const auto start = markov_texts::parseSequence(*(argv++));
        const auto length = *argv ? std::stoi(*(argv++)) : 10;
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
