#include "dictionary.h"

namespace markov_texts {

void DictionaryBuilder::add(const Sequence& sequence, const Word& nextWord)
{
    // TODO: Check that all sequencees are equal order.
    ++mData[sequence][nextWord];
}

void DictionaryBuilder::parse(std::istream& stream, size_t order)
{
    Sequence sequence;
    WordStream reader(stream);
    for (size_t i = 0; i < order; ++i)
    {
        if (auto word = reader.readToken())
            sequence.push_back(std::move(*word));
        else
            throw std::logic_error("Input stream is too short");
    }

    while (const auto word = reader.readToken())
    {
        add(sequence, *word);
        sequence.pop_front();
        sequence.push_back(std::move(*word));
    }
}

void DictionaryBuilder::save(std::ostream& stream) const
{
    WordStream writer(stream);
    for (const auto& data: mData)
    {
        for (const auto& word: data.first)
        {
            writer.write(word);
            writer.write(" ");
        }

        writer.write(":");
        for (const auto& count: data.second)
        {
            writer.write(" ");
            writer.write(count.first);
            writer.write(" ");
            writer.write(count.second);
        }

        writer.write(" |\n");
    }
}

boost::optional<const Word&> DictionaryGenerator::next(const Sequence& sequence) const
{
    auto countsIt = mData.find(sequence);
    if (countsIt == mData.end())
        return boost::none;

    const auto& counts = countsIt->second;
    const auto& maxSelect = counts.rbegin()->first;

    // TODO: make these generators thread safe?
    static std::random_device device;
    static std::mt19937 generator(device());
    std::uniform_int_distribution<size_t> distribution(0, maxSelect);

    const auto select = distribution(generator);
    return counts.lower_bound(select)->second;
}

void DictionaryGenerator::load(std::istream& stream)
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
