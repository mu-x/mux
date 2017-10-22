#include "word.h"

#include <stdexcept>
#include <QtCore/QRegExp>

namespace markov_texts {

// TODO: Add some other simbols as well?
static const QRegExp kPunctuation(R"re([\(\)\[\]\{\}\"\'\`\.\,\!\:\;])re");

Sequence parseSequence(const Word& word)
{
    Sequence sequence;
    for (auto& part: word.split(WordStream::kWordDelimiter))
        sequence.push_back(part.toLower());
    return sequence;
}

const Word WordStream::kWordDelimiter(" ");
const Word WordStream::kLineDelimiter("\n");

WordStream::WordStream(FILE* stream)
    : mStream(stream)
{
}

boost::optional<Word> WordStream::readToken()
{
    while (auto word = read())
    {
        word->remove(kPunctuation);
        if (!word->isEmpty())
            return word->toLower();
    }

    return boost::none;
}

Sequence WordStream::readSequence()
{
    Sequence sequence;
    while(auto word = readToken())
        sequence.push_back(std::move(*word));
    return sequence;
}

bool WordStream::checkStream() const
{
    if (mStream.status() == QTextStream::ReadPastEnd)
        return false;

    if (mStream.status() != QTextStream::Ok)
        throw std::runtime_error("I/O operation has failed");

    return true;
}

static WordStream* gDebugStream;

WordStream* debugStream()
{
    return gDebugStream;
}

void setDebugStream(WordStream* stream)
{
    gDebugStream = stream;
}

} // namespace markov_texts
