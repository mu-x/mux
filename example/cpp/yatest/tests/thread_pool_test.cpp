#include "yatest/thread_pool.hpp"
#include "yatest/trace.hpp"

#include <atomic>
#include <chrono>

#include <gtest/gtest.h>

namespace yatest {
namespace test {

TEST(ThreadPoolTest, Simple)
{
    std::atomic<size_t> count(0);
    std::function<void()> increment([&count](){ ++count; });

    {
        ThreadPool threadPool;
        for (int i = 0; i < 10; ++i)
            threadPool.schedule(increment);
    }

    ASSERT_EQ(10, count);
}

TEST(ThreadPoolTest, Future)
{
    std::atomic<size_t> count(0);
    std::function<size_t()> increment([&count](){ return count++; });

    ThreadPool threadPool;
    std::vector<std::future<size_t>> futures;
    for (size_t i = 0; i < 10; ++i)
        futures.push_back(threadPool.schedule(increment));

    size_t futureTotal(0), basicTotal(0);
    for (size_t i = 0; i < 10; ++i)
    {
        // order may be different but total the same
        basicTotal += i;
        futureTotal += futures[i].get();
    }

    ASSERT_EQ(basicTotal, futureTotal);
}

} // namespace test
} // namespace yatest

