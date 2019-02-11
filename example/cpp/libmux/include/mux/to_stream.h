#pragma once

#include <sstream>
#include <ios>
#include <typeinfo>
#include <optional>
#include <memory>
#include <typeinfo>
#include <iomanip>

#include "lang.h"

#ifdef MUX_BOOST_DEMANGLE
    #include <boost/core/demangle.hpp>
#endif

inline std::ostream& operator<<(std::ostream& stream, std::nullptr_t) { return stream << "nullptr"; }
inline std::ostream& operator<<(std::ostream& stream, std::nullopt_t) { return stream << "nullopt"; }

template<typename Value>
std::ostream& operator<<(std::ostream& stream, const std::optional<Value>& value);

inline
std::ostream& operator<<(std::ostream& stream, const std::type_info& info);

template<typename T, typename = typename std::enable_if<!std::is_integral<T>::value>::type>
std::ostream& operator<<(std::ostream& stream, const T* pointer);

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::unique_ptr<T>& pointer);

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<T>& pointer);

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::weak_ptr<T>& pointer);

template<typename First, typename Second>
std::ostream& operator<<(std::ostream& stream, const std::pair<First, Second>& value);

namespace mux {

template<typename Container>
class SteamableContainer {
public:
    SteamableContainer(
        const Container& container, 
        const char* begin = "{", const char* split = ", ", const char* end = "}");

    std::ostream& toStream(std::ostream& stream);

private:
    const Container& container_;
    const char* begin_; 
    const char* split_; 
    const char* end_;
};

template<typename Container>
std::ostream& operator<<(std::ostream& stream, const SteamableContainer<Container>& streamable);

/**
 * Usage:
 * ```
 *   std::set<std::string> types = {"a", "b", "c"};
 *   std::cout << steamable(types) << std::endl; // Output: {a, b, c}
 *   std::cout << steamable(types, "<", "/", ">") << std::endl; // Output: <a/b/c>
 * ``` 
 */
template<typename Container>
SteamableContainer<Container> steamable(const Container& container);

} // namespace mux

/**
 * Usage:
 * ```
 *   MUX_CONTAINER_STREAM_FOR(std::vector)
 *   MUX_CONTAINER_STREAM_FOR(std::map)
 *   ...
 *   std::vector<int> ints = {1, 2, 3, 4};
 *   std::cout << ints << std::endl; // Output: {1, 2, 3, 4}
 *   ...
 *   std::map<std::string, int> ids = {{"a", 1}, {"b", 2}};
 *   std::cout << ids << std::endl; // Output: {{a: 1}, {b: 2}}
 * ```
 */
#define MUX_TO_STREAM_FOR_CONTAINER(CONTAINER_TEMPLATE, BEGIN, SPLIT, END) \
    template<typename T> \
    std::ostream& operator<<(std::ostream& stream, const CONTAINER_TEMPLATE <T>& value) \
    { \
        return stream << mux::steamable(value, BEGIN, SPLIT, END); \
    } \

// --- IMPLEMENTATIONS

template<typename Value>
std::ostream& operator<<(std::ostream& stream, const std::optional<Value>& value)
{
    return value ? (stream << *value) : (stream << std::nullopt);
}

inline
std::ostream& operator<<(std::ostream& stream, const std::type_info& info)
{
    #ifdef MUX_BOOST_DEMANGLE
        return stream << boost::core::demangle(info.name());
    #else
        return stream << info.name();
    #endif 
}

template<typename T, typename = typename std::enable_if<!std::is_integral<T>::value>::type>
std::ostream& operator<<(std::ostream& stream, const T* pointer)
{
    const auto type = pointer ? typeid(*pointer) : typeid(T); 
    const auto flagsGuard = scopeGuard([&stream, flags = stream.flags()]{ stream.flags(flags); });
    return stream << type << "(" << std::hex << pointer << ")"; 
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::unique_ptr<T>& pointer)
{
    return stream << pointer.get();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<T>& pointer)
{
    return stream << pointer.get();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::weak_ptr<T>& pointer)
{
    return stream << pointer.lock();
}

template<typename First, typename Second>
std::ostream& operator<<(std::ostream& stream, const std::pair<First, Second>& value)
{
    return value.first << ": " << value.second;
}

namespace mux {

template<typename Container>
SteamableContainer<Container>::SteamableContainer(
    const Container& container, const char* begin, const char* split, const char* end)
:
    container_(container),
    begin_(begin), split_(split), end_(end_)
{
}

template<typename Container>
std::ostream& SteamableContainer<Container>::toStream(std::ostream& stream)
{
    stream << begin_;
    auto it = container_.begin();
    if (it != container_.end())
    {
        stream << *it;
        for (; it != container_.end(); ++it)
            stream << split_ << *it;
    }

    return stream << end_;
}

template<typename Container>
std::ostream& operator<<(std::ostream& stream, const SteamableContainer<Container>& streamable)
{
    return SteamableContainer(streamable.container).toStream(stream);
}

template<typename Container>
SteamableContainer<Container> steamable(const Container& container)
{ 
    return SteamableContainer<Container>(container); 
}

} // namespace mux
