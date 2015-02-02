#include "yatest/thread_pool.hpp"
#include "yatest/trace.hpp"
#include "yatest/word_counter.hpp"

#include <gtest/gtest.h>

namespace yatest {
namespace test {

TEST(WordCounterTest, Simple)
{
    WordCounter wc;
    EXPECT_FALSE(wc.countWord(""));

    EXPECT_TRUE(wc.countWord("hello", 2));
    EXPECT_TRUE(wc.countWord("world"));
    EXPECT_EQ(wc.count("hello"), 2);
    EXPECT_EQ(wc.count("world"), 1);
    EXPECT_EQ(wc.count("none"), 0);
}

static void expectEq(WordCounter::Counter&& c, const std::string& t)
{
    std::istringstream s(t);
    WordCounter left(std::move(c)), right(s);

    YATEST_DEBUG(left << " == " << right);
    EXPECT_EQ(left, right);
}

TEST(WordCounterTest, Count)
{
    expectEq({}, "");

    expectEq({ {"abc", 2}, {"def", 1}, {"klm", 1 } },
              "abc def,abc  *klm");

    expectEq({ {"9ab", 2}, {"zz0", 2}, {"zz0klm", 1}, {"t", 1}, {"r", 2} },
              "*9ab==zz0,zz0%zz0klm+=9ab))t<<!r!r!++");
}

TEST(WordCounterTest, Merge)
{
    WordCounter one({ {"a", 1}, {"b", 2}, {"c", 3 } });
    WordCounter two({ {"c", 2}, {"a", 1}, {"t", 1} });
    one.join(two);

    WordCounter res({ {"a", 2}, {"b", 2}, {"c", 5 }, {"t", 1} });
    EXPECT_EQ(one, res);
}

TEST(WordCounterTest, Top)
{
    WordCounter a({ {"a", 2}, {"b", 3}, {"c", 5 }, {"t", 1} });
    auto top = a.top(3);

    EXPECT_EQ(top[0], "c");
    EXPECT_EQ(top[1], "b");
    EXPECT_EQ(top[2], "a");
}

TEST(WordCounterTest, File)
{
    EXPECT_THROW(WordCounter::countFile("bla-bla-bla"), std::exception);

    auto top = WordCounter::countFile("tests/example/calculator.hpp").top(5);
    EXPECT_EQ(top[0], "uint64_t");
    EXPECT_EQ(top[1], "multiples");
}

TEST(WordCounterTest, Directory)
{
    ThreadPool threadPool;

    // manual directory count
    auto d = WordCounter::countFile("tests/example/calculator.hpp");
    d.join(WordCounter::countFile("tests/example/fme.hpp"));

    EXPECT_EQ(d, WordCounter::countDirectory("tests/example", threadPool));
    EXPECT_EQ(d, WordCounter::countDirectory("tests", threadPool));
}

} // namespace test
} // namespace yatest
