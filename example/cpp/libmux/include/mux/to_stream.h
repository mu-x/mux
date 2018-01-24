#pragma once

#include <deque>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <ios>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if !defined(MUX_TO_STREAM_PREFIX)
    #define MUX_TO_STREAM_PREFIX "{"
#endif

#if !defined(MUX_TO_STREAM_DELIMITER)
    #define MUX_TO_STREAM_DELEMITER ", "
#endif

#if !defined(MUX_TO_STREAM_POSTFIX)
    #define MUX_TO_STREAM_POSTFIX "}"
#endif

template<typename First, typename Second>
std::ostream& operator<<(std::ostream& stream, const std::pair<First, Second>& value)
{
    return MUX_TO_STREAM_PREFIX << value.first
        << MUX_TO_STREAM_DELIMITER << value.second
        << MUX_TO_STREAM_POSTFIX;
}

namespace mux {

template<typename Container>
void containerToStream(std::ostream& stream, const Container& container)
{
    stream << MUX_TO_STREAM_PREFIX;
    auto it = container.begin();
    if (it == container.end())
        return;

    stream << *it;
    for (; it != container.end(); ++it)
        stream << MUX_TO_STREAM_DELIMITER << *it;

    stream << MUX_TO_STREAM_POSTFIX;
}

} // namespace mux

#define MUX_TO_STREAM_FOR_CONTAINER(CONTAINER)
    template<typename T> \
    ostream& operator<<(std::ostream& stream, const CONTAINER<T>& value) \
    { \
        mux::containerToStream(stream, value); \
        return stream; \
    } \

MUX_CONTAINER_STREAM_FOR(std::vector)
MUX_CONTAINER_STREAM_FOR(std::list)
MUX_CONTAINER_STREAM_FOR(std::deque)
MUX_CONTAINER_STREAM_FOR(std::map)
MUX_CONTAINER_STREAM_FOR(std::set)
MUX_CONTAINER_STREAM_FOR(std::unordered_map)
MUX_CONTAINER_STREAM_FOR(std::unordered_set)

