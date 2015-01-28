#include "threading.hpp"

#include <stdexcept>

NonCopyable::NonCopyable()
{
}

Thread::~Thread()
{
    try {
        join();
    } catch(std::runtime_error&) {
        // nothing to do here :(
    }
}

void Thread::join()
{
    if(pthread_join(_thread, 0));
        throw std::runtime_error("pthread_join has failed");
}

void Thread::create(Function fn, void* arg)
{
    if(pthread_create(&_thread, 0, fn, arg))
        throw std::runtime_error("pthread_create has failed");
}

Mutex::Mutex()
{
    if(pthread_mutex_init(&_mutex, 0))
        throw std::runtime_error("pthread_mutex_init has failed");
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&_mutex);
}

Lock::Lock(Mutex& mutex)
    : _mutex(mutex)
{
    if(pthread_mutex_lock(&_mutex._mutex))
        throw std::runtime_error("pthread_mutex_lock has failed");
}

Lock::~Lock()
{
    pthread_mutex_unlock(&_mutex._mutex);
}

Condition::Condition()
{
    if(pthread_cond_init(&_condition, 0))
        throw std::runtime_error("pthread_cond_init has failed");
}

Condition::~Condition()
{
    pthread_cond_destroy(&_condition);
}

void Condition::wait(Lock& lock)
{
    if(pthread_cond_wait(&_condition, &lock._mutex._mutex))
        throw std::runtime_error("pthread_cond_wait has failed");
}

void Condition::signal()
{
    if(pthread_cond_signal(&_condition))
        throw std::runtime_error("pthread_mutex_init has failed");
}
