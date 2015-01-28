#include "calculator.hpp"

#include <stdexcept>

#ifdef DEBUG
    #include <iostream>
    static pthread_mutex_t _TRACE_mutex = PTHREAD_MUTEX_INITIALIZER;
    #define TRACE(arg) \
        pthread_mutex_lock(&_TRACE_mutex); \
        std::cerr << __PRETTY_FUNCTION__ << "(" << arg << ")" << std::endl; \
        pthread_mutex_unlock(&_TRACE_mutex);
#else
    #define TRACE(arg);
#endif

namespace lcm {

Calculator::Calculator(size_t threadCount)
    : _finish(false)
{
    TRACE(threadCount);

    // TODO: create specified exceptions for pthread calls
    if (pthread_mutex_init(&_mutex, 0))
        throw std::runtime_error("pthread_mutex_init has failed");
    if (pthread_cond_init(&_condition, 0))
        throw std::runtime_error("pthread_cond_init has failed");

    pthread_t thread;
    for (size_t i = 0; i != threadCount; ++i)
    {
        if (pthread_create(&thread, 0, &Calculator::threadWork, this))
            throw std::runtime_error("pthread_create has failed");
        _threads.push_back(thread);
    }
}

Calculator::~Calculator()
{
    stopAndWaitThreads();

    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_condition);
}

void Calculator::push(uint64_t number)
{
    TRACE(number);
    pthread_mutex_lock(&_mutex);
    {
        _queue.push_back(number);
        pthread_cond_signal(&_condition);
    }
    pthread_mutex_unlock(&_mutex);
}

Multiples Calculator::finalize()
{
    stopAndWaitThreads();

    // merge all of the results
    std::map<uint64_t, uint64_t> result;
    for (std::vector<Multiples>::const_iterator
            it = _maps.begin(); it != _maps.end(); ++it)
    {
        // TODO: look closer to STL for better algorithm
        for (Multiples::const_iterator ne = it->begin(); ne != it->end(); ++ne)
        {
            uint64_t& exp = result[ne->first];
            exp = std::max(exp, ne->second);
        }
    }

    return result;
}

void Calculator::stopAndWaitThreads()
{
    pthread_mutex_lock(&_mutex);
    {
        if (_finish)
        {
            pthread_mutex_unlock(&_mutex);
            return;
        }

        TRACE("FINISH");
        _finish = true;
        pthread_cond_signal(&_condition);
    }
    pthread_mutex_unlock(&_mutex);

    for (std::vector<pthread_t>::const_iterator
            it = _threads.begin(); it != _threads.end(); ++it)
        pthread_join(*it, 0);
}

void* Calculator::threadWork(void* arg)
{
    // FIXME: make wrapper function and catch std::exception for later
    //        forwarding to control thread
    Calculator& self = *static_cast<Calculator*>(arg);

    uint64_t number;
    Multiples multiples;

    while (true)
    {
        pthread_mutex_lock(&self._mutex);
        {
            while (self._queue.empty() && !self._finish)
            {
                TRACE("WAIT");
                pthread_cond_wait(&self._condition, &self._mutex);
            }

            if (self._queue.empty() && self._finish)
            {
                TRACE("FINISH");
                self._maps.push_back(multiples);

                pthread_cond_signal(&self._condition);
                pthread_mutex_unlock(&self._mutex);
                return 0;
            }

            number = self._queue.front();
            self._queue.pop_front();
        }
        pthread_mutex_unlock(&self._mutex);

        Multiples map = split(number);
        for (Multiples::iterator it = map.begin(); it != map.end(); ++it)
        {
            uint64_t& current = multiples[it->first];
            current = std::max(it->second, current);
        }
    }

    return 0;
}

Multiples Calculator::split(uint64_t number)
{
    TRACE(number);
    Multiples result;
    uint64_t base = 2;
    while (number && number != 1)
    {
        uint64_t exp = 0;
        while(number % base == 0)
        {
            number /= base;
            exp++;
        }

        if (exp)
            result[base] = exp;
        base++;
    }
    return result;
}

} // namespace lcm
