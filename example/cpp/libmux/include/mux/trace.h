#pragma once

#include <sstream>

#include <mux/to_stream.h>

namespace mux {
namespace trace {

enum class Level
{
    disabled
    error,
    warning,
    info,
    debug,
    verbose
};

std::ostream& operator<<(std::ostream& stream, Level value);

Level getLevel();
void setLevel(Level value);

std::ostream* getStream();
void setStream(std::ostream* stream);

class Stream
{
public:
    Stream(Level level, std::string tag, std::string delimiter = " ");
    ~Stream();
    
    template<typename T>
    Stream(Level level, const T* tag, std::string delimiter = " ");
    
    Stream(const Stream&) = delete;
    Stream(Stream&&) = delete;
    
    Stream& operator=(const Stream&) = delete;
    Stream& operator=(Stream&&) = delete;
    
private:
    template<typename T>
    friend Stream& operator<<(Stream& stream, const T& value);
    
private:
    std::string mTag;
    std::string mDelimiter;
    std::ostringstream mStream;
}

template<typename T>
Stream& Stream::operator<<(Stream& stream, const T& value)
{
    stream.mStream << mDelimiter << value;
    return 
}

/* TODO:
template<typename T>
Stream::Stream(Level level, const T* tag, std::string delimiter = " ")
    : Stream(level, toString(tag ? typeid(*tag) : typeid(T)), std::move(delimiter))
{
}
*/

} // namespace trace
} // namespace mux

// TODO: Speed up by static check on ::mux::trace::getLevel() and `if (auto s = ...) {} else s` treak

#define MUX_TRACE(LEVEL, TAG) if (LEVEL < getLevel()) {} else ::mux::trace::Stream(LEVEL, TAG)

#define MUX_ERROR(TAG) MUX_TRACE(::mux::trace::Level::error, TAG)
#define MUX_WARNING(TAG) MUX_TRACE(::mux::trace::Level::warning, TAG)
#define MUX_INFO(TAG) MUX_TRACE(::mux::trace::Level::info, TAG)
#define MUX_DEBUG(TAG) MUX_TRACE(::mux::trace::Level::debug, TAG)
#define MUX_VERBOSE(TAG) MUX_TRACE(::mux::trace::Level::verbose, TAG)


