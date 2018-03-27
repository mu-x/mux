#include "h.hpp"

namespace detail {

typedef int8_t No;
typedef int16_t Yes;

struct Any { template<typename T> Any(const T&); };
No test(const No&);

No operator<<(QDebug&, const Any&);
Yes test(const QDebug&);

No toString(const Any& any);
Yes test(const QString&);

template<typename T>
class exists
{
    static QDebug& m_stream;
    static const T& m_value;

public:
    static constexpr bool qdebug_operator =
        sizeof(test(m_stream << m_value)) == sizeof(Yes);

    static constexpr bool to_string =
        sizeof(test(toString(m_value))) == sizeof(Yes);
};

template<typename T>
constexpr bool exists<T>::qdebug_operator;

} // namespace detail

// ---

template<typename T>
QString toString(const T& value, decltype(&T::toString) = 0)
{
    return value.toString();
}

template<typename T>
QString toString(const T& value, typename std::enable_if<detail::exists<T>::qdebug_operator>::type* = 0)
{
    QString result;
    QDebug d(&result);
    d.noquote().nospace() << value;
    return result;
}

// --

template<typename T>
void PrintTo(const T& value, ::std::ostream* stream, typename std::enable_if<detail::exists<T>::to_string>::type* = 0)
{
    *stream << toString(value).toStdString();
}

// ---

struct A {
    QString toString() const { return "A"; }
};

struct B {};
QString toString(const B&) { return "B"; }


// ---

template<typename T>
void print(const T& v)
{
    mux::print(toString(v).toStdString());
}

int main(int, const char** /*argv*/)
{
    print(A());
    print(B());
    print(QSize());
    //print(std::vector<int>());

    PrintTo(A(), &std::cout);
    PrintTo(B(), &std::cout);
    PrintTo(QSize(), &std::cout);
    print(std::vector<int>());
}

