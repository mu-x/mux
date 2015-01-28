#ifndef LCM_CALCULATOR_HPP
#define LCM_CALCULATOR_HPP

#include <deque>
#include <map>
#include <vector>

#include <pthread.h>

// c++11 stdint.h workaround
typedef unsigned long long uint64_t;

namespace lcm {

const size_t DEFAULT_THREAD_COUNT = 4;

/** The Multiples Map, maps prime numbers to it's exponent */
typedef std::map<uint64_t, uint64_t> Multiples;

/** The Least Common Multiple Calculator */
class Calculator
{
public:
    /** Creates calc with @param threadCount threads */
    Calculator(size_t threadCount = DEFAULT_THREAD_COUNT);
    ~Calculator();

    /** Pushes the @param number for LCM split */
    void push(uint64_t number);

    /** Stops threads and calculates final numbers */
    Multiples finalize();

private:
    void stopAndWaitThreads();

    static void *threadWork(void* arg);
    static Multiples split(uint64_t number);

    // TODO: make wrappers and use then intead (e.g. boost)
    pthread_mutex_t _mutex;
    pthread_cond_t _condition;
    std::vector<pthread_t> _threads;

    std::deque<uint64_t> _queue;
    bool _finish;

    // NOTE: Not really good idea to keep it there and merge afterwards
    //       Horever the task asks so, let's leav it for optimization
    std::vector<Multiples> _maps;
};

} // namespace lcm

#endif // LCM_CALCULATOR_HPP
