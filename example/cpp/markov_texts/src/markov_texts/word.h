#pragma once

#include <stdexcept>
#include <deque>

#include <boost/optional.hpp>

#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QRegExp>

namespace markov_texts {

// TODO: Global string table with pointers would be a lot more efficient.
using Word = QString;

// TODO: Custom class with optimized hash calculation is prefered.
using Sequence = std::deque<Word>;

/** Word adapter for STL IO streams. */
class WordStream
{
public:
    template<typename StlStream>
    WordStream(StlStream& stream)
    : mStream(stream)
    {
    }

    /** @return nullopt in case of stream end. */
    template<typename T = Word>
    boost::optional<T> read()
    {
        T word;
        mStream >> word;

        if (mStream.status() == QTextStream::ReadPastEnd)
            return boost::none;

        if (mStream.status() != QTextStream::Ok)
            throw std::runtime_error("Input from stream has failed");

        return word;
    }

    /** Reads up to first valid token.
     *  @return nullopt in case of stream end. */
    inline
    boost::optional<Word> readToken()
    {
        // TODO: Move to cpp.
        while (auto word = read())
        {
            // TODO: Remove some other simbols as well?
            static const QRegExp kPunctuation("[()[]{}.,!:;]");
            word->remove(kPunctuation);
            if (!word->isEmpty())
                return word->toLower();;
        }

        return boost::none;
    }

    /** Reads up words up to end of stream. */
    inline
    Sequence readSequence()
    {
        // TODO: Move to cpp.
        Sequence sequence;
        while(auto word = readToken())
            sequence.push_back(std::move(*word));
        return sequence;
    }

    template<typename T>
    void write(const T& value)
    {
        mStream << value;
        if (mStream.status() != QTextStream::Ok)
            throw std::runtime_error("Write to stream has failed");
    }

private:
    QTextStream mStream;
};

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
