#ifndef YATEST_WORD_COUNTER_HPP
#define YATEST_WORD_COUNTER_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace yatest {

class ThreadPool;

/** Counts words and keep them in the internal storage */
class WordCounter
{
public:
    typedef std::unordered_map<std::string, size_t> Counter;

    /** Empty word counter */
    WordCounter() = default;

    /** Counts words in the stream @param is */
    WordCounter(std::istream& is);

    /** Builds counter based on counts */
    WordCounter(Counter&& wc);

    /** Compairs this counters to @param wc */
    bool operator ==(const WordCounter& wc) const;

    /** Adds counts from @param wc to the current counter */
    void join(const WordCounter& wc);

    /** Returns @param count most common words (biggest counters) */
    std::vector<std::string> top(size_t count) const;

    /** Counts @param word (if non-empty) @param count times,
     *  returns if the word was counted */
    bool countWord(const std::string& word, size_t count = 1);

    /** Returns @param word count */
    size_t count(const std::string& word) const;

    /** Counts words in the file by @param path */
    static WordCounter countFile(const std::string& path);

    /** Recursively counts words in the directory by @param path. Files are
     *  getting processed asyncronusly using @param threadPool */
    static WordCounter countDirectory(const std::string& path,
                                      ThreadPool& threadPool);
private:
    friend std::ostream& operator <<(std::ostream& os, const WordCounter& wc);
    Counter counter_;
};

} // namespace yatest

#endif // YATEST_WORD_COUNTER_HPP
