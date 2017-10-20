#pragma once

#include <boost/optional.hpp>
#include <deque>
#include <QtCore/QString>
#include <QtCore/QTextStream>

namespace markov_texts {

// TODO: Global string table with pointers would be a lot more efficient.
using Word = QString;

// TODO: Custom class with optimized hash calculation is prefered.
using Sequence = std::deque<Word>;

/** Makes sequence from string. */
Sequence parseSequence(const Word& word);

/** Word adapter for STL IO streams. */
class WordStream
{
public:
    static const Word kWordDelimiter;
    static const Word kLineDelimiter;

    template<typename Stream>
    WordStream(Stream& stream);

    /** @return nullopt in case of stream end. */
    template<typename T = Word>
    boost::optional<T> read();

    /** Reads up to first valid token.
     *  @return nullopt in case of stream end. */
    boost::optional<Word> readToken();

    /** Reads up words up to end of stream. */
    Sequence readSequence();

    template<typename T>
    void write(const T& value);

    template<typename T, typename ... Args>
    void write(const T& value, const Args& ... moreValues);

private:
    bool checkStream() const;
    QTextStream mStream;
};

WordStream* debugStream();
void setDebugStream(WordStream* stream = nullptr);

template<typename ... Args>
void debug(const Args& ... args)
{
    if (const auto stream = debugStream())
        stream->write(args ..., WordStream::kLineDelimiter);
}

} // namespace markov_texts
namespace std {

template<>
struct hash<markov_texts::Word>
{
    size_t operator()(const markov_texts::Word& w) const
    {
        return static_cast<size_t>(qHash(w));
    }
};

template<>
struct hash<markov_texts::Sequence>
{
    size_t operator()(const markov_texts::Sequence& s) const
    {
        std::hash<markov_texts::Word> hash;
        size_t result = 0;
        for (const auto& w: s)
            result ^= hash(w);
        return result;
    }
};

} // namespace std
namespace markov_texts {

template<typename Stream>
WordStream::WordStream(Stream& stream)
    : mStream(stream)
{
}

/** @return nullopt in case of stream end. */
template<typename T>
boost::optional<T> WordStream::read()
{
    T item;
    mStream >> item;
    return checkStream() ? item : boost::optional<T>();
}

template<typename T>
void WordStream::write(const T& value)
{
    mStream << value;
    checkStream();
}

template<typename T, typename ... Args>
void WordStream::write(const T& value, const Args& ... moreValues)
{
    write(value);
    write(moreValues ...);
}

} // namespace markov_texts
