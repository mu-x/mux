#ifndef THREADING_HPP
#define THREADING_HPP

#include <pthread.h>

class NonCopyable
{
    NonCopyable(const NonCopyable&);
    NonCopyable& operator =(const NonCopyable&);

public:
    NonCopyable();
};

/** The Thead wrapper
 *
 * Usage:
 *  Object object;
 *  Thread thread(object, &Object::doStuff); */
class Thread : NonCopyable
{
    typedef void* (*Function)(void*);

public:
    template<typename T>
    Thread(T& object, void (T::*method)())
    {
        create((Function&)method, &object);
    }

    ~Thread();

    void join();

private:
    void create(Function fn, void* arg);

    pthread_t _thread;
};

/** The Mutex wrapper */
class Mutex : NonCopyable
{
public:
    Mutex();
    ~Mutex();

private:
    friend class Lock;
    friend class Condition;

    pthread_mutex_t _mutex;
};

/** The @class Mutex's lock guard
 *
 * Usage:
 *  Mutex mutex;
 *  { Lock lock(mutex); doSyncStuff(); } */
class Lock : NonCopyable
{
public:
    Lock(Mutex& mutex);
    ~Lock();

private:
    friend class Condition;

    Mutex& _mutex;
};

/** The Condition variable wrapper */
class Condition : NonCopyable
{
public:
    Condition();
    ~Condition();

    void wait(Lock& lock);
    void signal();

private:
    pthread_cond_t _condition;
};

#endif
