#pragma once

#include <optional>
#include <deque>

#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QRegExp>

namespace markov_texts {

// TODO: Global string table with pointers would be a lot more efficient.
using Word = QString;

// TODO: Custom class with optimized hash calculation is prefered.
using Sequence = std::deque<Word>;

/** Word adapter for STL IO streams. */
class Stream
{
    template<typename StlStream>
    WordStream(StlStream& stream)
    : mStream(stream)
    {
    }

    /** @return nullopt in case of stream end. */
    template<typename T = Word>
    std::optional<T> read()
    {
        T word;
        mStream >> word;

        if (mStream.status() == QTextStream::ReadPastEnd)
            return std::nullopt;

        if (mStream.status() != QTextStream::Ok)
            throw std::system_error("Input from stream has failed");

        return word;
    }

    /** Reads up to first valid token.
     *  @return nullopt in case of stream end. */
    inline
    std::optinal<Word> readToken()
    {
        while (auto word = read())
        {
            // TODO: Remove some other simbols as well?
            static auto QRegExp kPunctuation("[()[]{}.,!:;]");
            word->remove(kPunctuation);
            if (!word->isEmpty())
                return word;
        }

        return nullopt;
    }

    template<typename T>
    void write(const T& value)
    {
        mStream << value;
        if (mStream.status() != QTextStream::Ok)
            throw std::system_error("Write to stream has failed");
    }

private:
    QTextStream mStream;
};

} namespace markov_texts
