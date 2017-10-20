#include <iostream>
#include <markov_texts/dictionary.h>

int main(int, char** argv)
{
    ++argv; // Binary;
    try
    {
        markov_texts::WordStream debugStream(stderr);
        if (*argv && *(argv++) == std::string("--verbose"))
            markov_texts::setDebugStream(&debugStream);

        int order = *argv ? std::stoi(*(argv++)) : 1;
        if (order <= 0)
            throw std::invalid_argument("Wrong order paramiter");

        markov_texts::DictionaryBuilder dictionary;
        dictionary.parse(stdin, static_cast<size_t>(order));
        dictionary.save(stdout);
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
}
