#include <cstring>
#include <cstdlib>

#include <fstream>
#include <future>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <type_traits>
#include <vector>

#if defined(__linux__)
    #include <pwd.h>
    #include <sys/prctl.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif // defined(__linux__)

#if defined(_WIN32)
    #include <winsock2.h>
    #include <windows.h>
#endif // defined(__linux__)

#if defined(BOOST)
    #include <boost/thread.hpp>
    #include <boost/optional.hpp>
#endif // defined(BOOST)

#if defined(QT)
    #include <QtCore/QDebug>
    #include <QtCore/QRegExp>
    #include <QtCore/QMutex>
    #include <QtCore/QByteArray>
    #include <QtCore/QString>
    #include <QtCore/QUrl>
    #include <QtCore/QSize>
#endif // defined(QT)

namespace mux {

template<typename Value>
void print(const Value& value)
{
    std::cout << value << std::endl;
}

template<typename Value, typename ... Values>
void print(const Value& value, const Values& ... values)
{
    std::cout << value << " ";
    print(values ...);
}

struct Args
{
    const std::string binary;
    const std::vector<std::string> args;

    inline
    Args(const char** argv)
        : binary(*argv)
        , args(parse(argv))
    {
    }

    inline
    static std::vector<std::string> parse(const char** argv)
    {
        std::vector<std::string> list;
        for (auto arg = argv; *arg; ++arg)
            list.push_back(*arg);
        return list;
    }
};

template <typename T>
class Traceble
{
public:
    Traceble()
    {
        mux::print("Traceble()");
    }
    template<typename ... Args>
    Traceble(Args ... args)
        : data_(std::forward<Args>(args) ...)
    {
        mux::print("Traceble(", data_, ")");
    }
    ~Traceble()
    {
        mux::print("~Traceble(", data_, ")");
    }

    void set(T data)
    {
        data_ = std::move(data);
        mux::print("Traceble::set(", data_, ")");
    }
    const T& get() const
    {
        return data_;
    }
    void print() const
    {
        mux::print("Traceble::print(", data_, ")");
    }

    Traceble(const Traceble& rhs)
        : data_(rhs.data_)
    {
        mux::print("Traceble(", data_, ")");
    }
    Traceble(Traceble&& rhs)
        : data_(std::move(rhs.data_))
    {
        mux::print("Traceble&&(", data_, ")");
    }

    Traceble& operator=(const Traceble& rhs)
    {
        data_ = rhs.data_;
        mux::print("Traceble::=(", data_, ")");
        return *this;
    }
    Traceble& operator=(Traceble&& rhs)
    {
        data_ = std::move(rhs.data);
        mux::print("Traceble::=&&(", data_, ")");
        return *this;
    }

private:
    T data_;
};

} // namespace mux

#define MUX_TRACE(EXPRESSION) mux::print(#EXPRESSION, "=", EXPRESSION)

