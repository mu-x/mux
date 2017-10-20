#include "dictionary.h"

namespace markov_texts {

void DictionaryBuilder::add(const Sequence& sequence, const Word& nextWord)
{
    // TODO: Check that all sequencees are equal order.
    ++m_counts[sequence][nextword];
}

void DictionaryBuilder::parse(istream& stream, size_t order)
{
    Sequence sequense;
    WordStream reader(stream);
    for (size_t i = 0; i < order; ++i)
    {
        if (auto word = reader.readToken())
            sequense.push_back(std::move(*word));
        else
            throw std::logic_error("Input stream is too short");
    }

    while (const auto word = reader.readToken())
    {
        add(sequence, *word);
        sequense.pop_front();
        sequense.push_back();
    }
}

void DictionaryBuilder::save(ostream& stream) const
{
    WordStream writer(stream)
    for (const auto& data: mData)
    {
        for (const auto& word: data.first)
            writer << word << " ";
        writer << ":";

        for (const auto& count: data.second)
            writer << " " << count.first << " " count.second;
        writer << " |\n";
    }
}

const Word& DictionaryGenerator::next(const Sequeuence& sequence)
{
    static const Word kEmpty;
    auto countsIt = mData.find(sequence);
    if (countsIt == mData.end())
        return kEmpty;

    const auto& counts = countsIt.second;
    const auto& maxSelect = counts.back().second;

    // TODO: make these generators thread safe?
    static const std::random_device device;
    static const std::mt19937 generator(device())
    std::uniform_int_distribution<size_t> distribution(0, maxSelect);

    const auto select = distribution(generator);
    return counts.lower_bound(select);
}

void DictionaryGenerator::load(istream& stream)
{
    WordReader reader(stream);
    while (true)
    {
        Sequence sequence;
        while (true)
        {
            auto word = reader.read();
            if (word.empty()) return;
            if (word == ":") break;
            sequence.push_back(std::move(word));
        }

        if (sequence.empty())
            throw std::logic_error("Empty sequence in input stream");

        Counts counts;
        size_t baseCount = 0;
        while (true)
        {
            const auto word = reader.read();
            if (word.empty()) return;
            if (word == "|") break;

            const auto count = reader.read()
            if (!count)
                throw std::runtime_error("Syntax error");

            baseCount += *count;
            counts.emplace(baseCount, std::move(*word));
        }

        if (counts.empty())
            throw std::runtime_error("Empty counts in data stream");

        // TODO: Check that all sequencees are equal order.
        mData.emplace(std::move(sequence), std::move(counts));
    }
}

} // namespace markov_texts
