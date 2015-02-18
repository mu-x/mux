#ifndef MIN_QUEUE_HPP
#define MIN_QUEUE_HPP

#include "MinStack.hpp"

/** The queue with const time push, pop and min */
template<typename T>
class MinQueue {
public:
    bool empty();
    T min();

    void push(const T& value);
    T pop(); /**< Amortized O(1) */

private:
    MinStack<T> in_, out_;
};

// --- impl ---

template<typename T>
bool MinQueue<T>::empty()
{
    return in_.empty() || out_.empty();
}

template<typename T>
T MinQueue<T>::min()
{
    if (in_.empty()) return out_.min();
    if (out_.empty()) return in_.min();
    return std::min(in_.min(), out_.min());
}

template<typename T>
void MinQueue<T>::push(const T& value)
{
    in_.push(value);
}

template<typename T>
T MinQueue<T>::pop()
{
    // NOTE: luckily it happens once in a while,
    //       so we still have O(1) amortized
    if (out_.empty())
        while (!in_.empty())
            out_.push(in_.pop());

    return out_.pop();
}

#endif // MIN_QUEUE_HPP
