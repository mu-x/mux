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
    void parse(std::istream& istream, size_t order);

    /** Writes data to a stream. */
    void save(std::ostream& stream) const;

    // TODO: Some generic methods.

private:
    using Counts = std::unordered_map<Word, size_t>;
    std::unordered_map<Sequence, Counts> mData;

};

/** Generates markov chain by dictionary. */
class DictionaryGenerator
{
public:
    /** Generates next random word. */
    boost::optional<const Word&> next(const Sequence& sequence) const;

    /** Generates continuation of start and prints it to stream. */
    void generate(const Sequence& start, std::ostream& stream, size_t newWords) const;

    /** Loads dictionary from stream. */
    void load(std::istream& stream);

    // TODO: More generic methods.

private:
    // TODO: vector with binary search would be a little more eficient.
    using Counts = std::map<size_t, Word>;
    std::unordered_map<Sequence, Counts> mData;
};

} namespace markov_texts
