#include "yatest/thread_pool.hpp"
#include "yatest/trace.hpp"

#ifdef __linux__
    #include <unistd.h>
    #define CPU_CORE_COUNT sysconf(_SC_NPROCESSORS_ONLN)
#else
    #define CPU_CORE_COUNT 4
#endif

namespace yatest {

static void serviceRun(boost::asio::io_service* service)
{
    YATEST_DEBUG("begin");
    // TODO: take care of exception handling
    try
    {
        service->run();
    }
    catch (const std::exception& ex)
    {
        YATEST_EXCEPTION(ex.what());
    }
    catch (...)
    {
        YATEST_EXCEPTION("unknown");
    }
    YATEST_DEBUG("end");
}

ThreadPool::ThreadPool(size_t threadCount)
    : service_(threadCount)
    , work_(new boost::asio::io_service::work(service_))
{
    YATEST_DEBUG(threadCount << " threads");
    for (size_t i = 0; i < threadCount; ++i)
        threads_.push_back(std::thread(serviceRun, &service_));
}

ThreadPool::~ThreadPool()
{
    work_.reset();
    YATEST_DEBUG("joining " << threads_.size() << " threads");
    for (auto it = threads_.begin(); it != threads_.end(); ++it)
        it->join();
}

void ThreadPool::schedule(const std::function<void()>& task)
{
    service_.post(task);
}

size_t ThreadPool::cpuCoreCount()
{
    return static_cast<size_t>(CPU_CORE_COUNT);
}

} // namespace yatest

