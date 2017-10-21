#include "dictionary.h"

namespace markov_texts {

const Word kCountersBeginToken("{");
const Word kCountersEndToken("}");

void DictionaryBuilder::add(const Sequence& sequence, const Word& nextWord)
{
    if ((mOrder && sequence.size() != mOrder) || sequence.empty())
        throw std::logic_error("Unexpected sequence length");

    mOrder = sequence.size();
    ++mData[sequence][nextWord];
}

void DictionaryBuilder::parse(FILE* stream, size_t order)
{
    debug("Parsing stream with order ", order);

    Sequence sequence;
    WordStream reader(stream);
    for (size_t i = 0; i < order; ++i)
    {
        if (auto word = reader.readToken())
            sequence.push_back(std::move(*word));
        else
            throw std::logic_error("Input stream is too short for selected order");
    }

    while (const auto word = reader.readToken())
    {
        add(sequence, *word);
        sequence.pop_front();
        sequence.push_back(std::move(*word));
    }
}

void DictionaryBuilder::save(FILE* stream) const
{
    debug("Saving dictionary to stream");

    WordStream writer(stream);
    for (const auto& data: mData)
    {
        for (const auto& word: data.first)
            writer.write(word, WordStream::kWordDelimiter);

        writer.write(kCountersBeginToken);
        for (const auto& count: data.second)
        {
            writer.write(WordStream::kWordDelimiter, count.first);
            writer.write(WordStream::kWordDelimiter, count.second);
        }

        writer.write(WordStream::kWordDelimiter, kCountersEndToken, WordStream::kLineDelimiter);
    }
}

boost::optional<const Word&> DictionaryGenerator::next(const Sequence& sequence) const
{
    if (mOrder && sequence.size() != mOrder)
        throw std::logic_error("Unexpected sequence length");

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

void DictionaryGenerator::generate(const Sequence& start, FILE* stream, size_t newWords) const
{
    debug("Generating ", newWords, " new words");

    if (!mOrder)
        throw std::logic_error("Unable to generate from empty dictionary");

    if (start.size() != mOrder)
        throw std::logic_error("Start sequence has incorrect size");

    WordStream writer(stream);
    for (const auto& word: start)
        writer.write(word, WordStream::kWordDelimiter);

    Sequence sequence(start);
    for (size_t i = 0; i < newWords; ++i)
    {
        auto word = next(sequence);
        if (!word)
        {
            writer.write(WordStream::kLineDelimiter);
            debug("Warning: unable to find sequence, only ", i, " words generated");
            return;
        }

        writer.write(*word, WordStream::kWordDelimiter);
        sequence.pop_front();
        sequence.push_back(std::move(*word));
    }

    writer.write(WordStream::kLineDelimiter);
}

void DictionaryGenerator::load(FILE* stream)
{
    debug("Loading dictionary from stream");

    WordStream reader(stream);
    while (true)
    {
        Sequence sequence;
        while (true)
        {
            auto word = reader.read();
            if (!word)
                return;

            if (*word == kCountersBeginToken)
                break;

            sequence.push_back(std::move(*word));
        }

        if ((mOrder && sequence.size() != mOrder) || sequence.empty())
        {
            debug("Sequence size ", sequence.size(), " line ", mData.size() - 1);
            throw std::logic_error("Unexpected sequence length in input stream");
        }
        mOrder = sequence.size();

        Counts counts;
        size_t baseCount = 0;
        while (true)
        {
            const auto word = reader.read();
            if (!word)
                return;

            if (*word == kCountersEndToken)
                break;

            const auto count = reader.read<size_t>();
            if (!count)
                throw std::runtime_error("Syntax error in input stream");

            baseCount += *count;
            counts.emplace(baseCount, std::move(*word));
        }

        if (counts.empty())
            throw std::runtime_error("Empty counts in input stream");

        mData.emplace(std::move(sequence), std::move(counts));
    }
}

} // namespace markov_texts
