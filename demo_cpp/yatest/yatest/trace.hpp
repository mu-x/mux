#ifndef YATEST_TRACE_HPP
#define YATEST_TRACE_HPP

#include <iostream>
#include <mutex>
#include <thread>

namespace yatest {

struct Trace
{
    static std::mutex mutex_;
};

#define YATEST_CONTEXT                                                      \
    std::this_thread::get_id() << ": " << __PRETTY_FUNCTION__  << " -- "

#define YATEST_TRACE(content) {                                             \
        std::lock_guard<std::mutex> __guard_(Trace::mutex_);                \
        std::cerr << YATEST_CONTEXT << content << std::endl;                \
    }

#define YATEST_EXCEPTION(content) YATEST_TRACE("Exception caught: " << content)

#ifdef DEBUG
    #define YATEST_DEBUG(content) YATEST_TRACE(content)
#elif !DEBUG
    #define YATEST_DEBUG(content)
#endif

} // namespace yatest

#endif // YATEST_TRACE_HPP
