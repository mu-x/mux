#include "yatest/word_counter.hpp"
#include "yatest/thread_pool.hpp"
#include "yatest/trace.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <boost/filesystem.hpp>

namespace yatest {

WordCounter::WordCounter(std::istream& is)
{
    char c;
    std::ostringstream ss;
    while(is.get(c))
    {
        if (std::isalnum(c) || c == '_')
        {
            ss << static_cast<char>(std::tolower(c));
            continue;
        }

        if (countWord(ss.str()))
            ss.str(std::string());
    }

    countWord(ss.str());
}

WordCounter::WordCounter(Counter&& counter)
    : counter_(std::move(counter))
{
}

bool WordCounter::operator ==(const WordCounter& wc) const
{
    return counter_ == wc.counter_;
}

void WordCounter::join(const WordCounter& wc)
{
    YATEST_DEBUG(wc);
    for (auto& it : wc.counter_)
        countWord(it.first, it.second);
}

typedef WordCounter::Counter::const_iterator WcIter;
static bool lessWcIter(const WcIter& left, const WcIter& right)
{
    return left->second < right->second;
}

std::vector<std::string> WordCounter::top(size_t count) const
{
    size_t countFix = std::min(count, counter_.size());
    YATEST_DEBUG(count << " reduce to " << countFix);

    std::vector<Counter::const_iterator> sorted;
    for (auto it = counter_.begin(); it != counter_.end(); ++it)
        sorted.push_back(it);

    // TODO: find out if algorithm is efficient
    std::sort(sorted.begin(), sorted.end(), lessWcIter);

    std::vector<std::string> top;
    for (auto it = sorted.rbegin(); it != sorted.rbegin() + countFix; ++it)
    {
        YATEST_DEBUG("select " << (**it).first << " for " << (**it).second);
        top.push_back((**it).first);
    }

    return top;
}

size_t WordCounter::count(const std::string& word) const
{
    auto it = counter_.find(word);
    if (it != counter_.end()) return it->second;
    return 0;
}

bool WordCounter::countWord(const std::string& word, size_t count)
{
    if (word.size())
    {
        auto& counter = counter_[word];
        counter += count;
        YATEST_DEBUG(word << " += " << count << " -> " << counter);
        return true;
    }

    return false;
}

WordCounter WordCounter::countFile(const std::string& path)
{
    YATEST_DEBUG(path);
    std::ifstream file(path);
    if (file) return WordCounter(file);

    std::ostringstream ss;
    ss << "Can not open file: " << path;
    throw std::invalid_argument(ss.str());
}

void collectDirectory(const boost::filesystem::path& path,
                      ThreadPool& threadPool,
                      std::vector<std::future<WordCounter>>& futures)
{
    YATEST_DEBUG(path);
    namespace fs = boost::filesystem;
    fs::directory_iterator end;
    for (fs::directory_iterator it(path); it != end; ++it)
    {
        if (fs::is_directory(*it))
        {
            collectDirectory(*it, threadPool, futures);
            continue;
        }

        std::string file = it->path().string();
        if (file.substr(file.find_last_of(".") + 1) == "hpp")
            futures.push_back(threadPool.schedule(std::function<WordCounter()>(
                [file](){ return WordCounter::countFile(file); })));
    }
}

WordCounter WordCounter::countDirectory(const std::string& path,
                                        ThreadPool& threadPool)
{
    // NOTE: With normal HDD (not SSD or RAM) this method is not really
    //       efficient because of IO bottleneck

    YATEST_DEBUG(path);
    std::vector<std::future<WordCounter>> futures;
    collectDirectory(boost::filesystem::path(path), threadPool, futures);

    WordCounter wordCounter;
    for (auto& future : futures)
        wordCounter.join(future.get());

    return wordCounter;
}

std::ostream& operator <<(std::ostream& os, const WordCounter& wc)
{
    os << "WordCounter";
    for (const auto& it : wc.counter_)
        os << " " << it.first << " = " << it.second;
    return os;
}

} // namespace yatest

