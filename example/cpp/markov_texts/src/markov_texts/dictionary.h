#pragma once

#include <istream>
#include <map>
#include <ostream>
#include <unordered_map>

#include "word.h"

namespace markov_texts {

/** Builds dictionary for Markov chain. */
class DictionaryBuilder
{
public:
    /** Adds a new word accurence. */
    void add(const Sequence& sequence, const Word& nextWord);

    /** Parses stream to find files. */
    void parse(FILE* stream, size_t order);

    /** Writes data to a stream. */
    void save(FILE* stream) const;

    // TODO: Some generic methods.

private:
    using Counts = std::unordered_map<Word, size_t>;
    std::unordered_map<Sequence, Counts> mData;
    boost::optional<size_t> mOrder;

};

/** Generates markov chain by dictionary. */
class DictionaryGenerator
{
public:
    /** Generates next random word. */
    boost::optional<const Word&> next(const Sequence& sequence) const;

    /** Generates continuation of start and prints it to stream. */
    void generate(const Sequence& start, FILE* stream, size_t newWords) const;

    /** Loads dictionary from stream. */
    void load(FILE* stream);

    // TODO: More generic methods.

private:
    // TODO: vector with binary search would be a little more eficient.
    using Counts = std::map<size_t, Word>;
    std::unordered_map<Sequence, Counts> mData;
    boost::optional<size_t> mOrder;
};

} // namespace markov_texts
