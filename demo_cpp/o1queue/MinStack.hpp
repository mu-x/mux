#ifndef MIN_STACK_HPP
#define MIN_STACK_HPP

#include <stack>

/** The stack with const time push, pop and min */
template<typename T>
class MinStack
{
public:
    bool empty() const;
    T min() const;

    void push(const T& value);
    T pop();

private:
    typedef std::pair<T, T> Item;
    std::stack<Item> stack_;
};

// TODO: enhance template paramiters:
//       typename Container = std::deque<T> -> std::stack<Item, Container>
//       typename Comparator = std::less<T> -> std::min(_, _, comp)

// --- impl ---

template<typename T>
bool MinStack<T>::empty() const
{
    return stack_.empty();
}
template<typename T>
T MinStack<T>::min() const
{
    return stack_.top().second;
}

template<typename T>
void MinStack<T>::push(const T& value)
{
    stack_.push(std::make_pair(
        value,
        empty() ? value : std::min(value, min())
    ));
}

template<typename T>
T MinStack<T>::pop()
{
    T top = stack_.top().first;
    stack_.pop();
    return top;
}

#endif // MIN_STACK_HPP
