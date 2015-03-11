#ifndef YATEST_THREAD_POOL_HPP
#define YATEST_THREAD_POOL_HPP

#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <vector>

#include <boost/asio/io_service.hpp>
#include <boost/noncopyable.hpp>

namespace yatest {

/** The Thread Pool executor */
class ThreadPool
    : boost::noncopyable
{
public:
    /** Creates the pool with @param threadCount threads */
    ThreadPool(size_t threadCount = cpuCoreCount());
    ~ThreadPool();

    /** Shedules the @param task for async execution */
    void schedule(const std::function<void()>& task);

    /** Shedules the @param task for async execution, returns future */
    template<typename T>
    std::future<T> schedule(const std::function<T()>& task);

    /** Returns CPU core count for current PC */
    static size_t cpuCoreCount();

private:
    boost::asio::io_service service_;
    std::shared_ptr<boost::asio::io_service::work> work_;
    std::vector<std::thread> threads_;
};

// -----------------------------------------------------------------------------

template<typename T>
std::future<T> ThreadPool::schedule(const std::function<T()>& task)
{
    auto p = std::make_shared<std::promise<T>>();
    schedule(std::function<void()>([p, task](){ p->set_value(task()); }));
    return p->get_future();
}

} // namespace yatest

#endif // YATEST_THREAD_POOL_HPP
