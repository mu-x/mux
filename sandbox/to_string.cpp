#include "h.hpp"

namespace kaka { struct K {}; }
struct K {};


//----------------------------------------------------------------------------------------

namespace detail {

typedef int8_t No;
typedef int16_t Yes;

struct Any { template<typename T> Any(const T&); };

No operator<<(QDebug&, const Any&);
No toString(const Any& any);
No test(const No&);
Yes test(const QDebug&);
Yes test(const QString&);

template<typename T>
class StringSupport
{
    static QDebug& m_stream;
    static const T& m_value;

    template<typename C>
    static Yes testMethod(decltype(&C::toString));

    template<typename C>
    static No testMethod(...);

public:
    static constexpr bool qdebug = sizeof(test(m_stream << m_value)) == sizeof(Yes);
    static constexpr bool function = sizeof(test(toString(m_value))) == sizeof(Yes);
    static constexpr bool method = sizeof(testMethod<T>(0)) == sizeof(Yes);
};

template<typename T> constexpr bool StringSupport<T>::qdebug;
template<typename T> constexpr bool StringSupport<T>::function;
template<typename T> constexpr bool StringSupport<T>::method;

template<typename T, typename = typename std::enable_if_t<
    StringSupport<T>::method || StringSupport<T>::function || StringSupport<T>::qdebug
>>
QString qtString(const T& value)
{
    if constexpr (StringSupport<T>::method)
        return value.toString();

    if constexpr (StringSupport<T>::function)
        return ::toString(value);

    QString result;
    QDebug d(&result);
    d.noquote().nospace() << value;
    return result;
}

template<typename T, typename = typename std::enable_if_t<
    detail::StringSupport<T>::method || detail::StringSupport<T>::function
>>
std::ostream& operator<<(std::ostream& stream, const T& value)
{
    const auto string = detail::qtString(value).toStdString();
    return stream << string;
}


} // namespace detail

using detail::operator<<;

//------------------------------------------------------------------------------------------------

namespace ns {

struct A {
    QString toString() const { return "A"; }
};

struct AF;

struct B {};
QString toString(const B&) { return "B"; }

enum E {};
QString toString(const E&) { return "E"; }

enum class EC {};
QString toString(const EC&) { return "EC"; }

} // namespace ns


// ---

#define TRAITS(T) \
    mux::print(#T, \
        detail::StringSupport<T>::qdebug, detail::StringSupport<T>::function, detail::StringSupport<T>::method)

template<typename T>
void print(const T& v)
{
    std::cout << v << std::endl;
    //mux::print(detail::qtString(v).toStdString());
}

int main(int, const char** /*argv*/)
{
    TRAITS(ns::A);
    TRAITS(ns::B);
    TRAITS(QSize);
    print(ns::A());
    print(ns::B());
    //print(QSize());
    print(ns::E());
    print(ns::EC());
    print(kaka::K());
    print(K());
    //print(ns::AF());
}

