#pragma once

#include <sstream>

#include <mux/to_stream.h>

namespace mux {
namespace trace {

enum class Level
{
    disabled,
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
    Stream(Level level, std::string tag, const char* delimiter = " ");
    ~Stream();
    
    template<typename T>
    Stream(Level level, const T* tag, const char* delimiter = " ")
        : Stream(level, toString(tag), std::move(delimiter)) {}
    
    Stream(const Stream&) = delete;
    Stream(Stream&&) = delete;
    
    Stream& operator=(const Stream&) = delete;
    Stream& operator=(Stream&&) = delete;
    
    template<typename T>
    Stream& print(const T& value) { return stream_ << delimiter_ << value; }
    
private:
    const Level level_;
    const std::string tag_;
    const char* const delimiter_;
    std::ostringstream stream_;
};

template<typename T>
Stream& operator<<(Stream& stream, const T& value) { return stream.print(value); }

} // namespace trace
} // namespace mux

// TODO: Speed up by static check on ::mux::trace::getLevel() and `if (auto s = ...) {} else s` treak

#define MUX_TRACE(LEVEL, TAG) if (LEVEL < getLevel()) {} else ::mux::trace::Stream(LEVEL, TAG)

#define MUX_ERROR(TAG) MUX_TRACE(::mux::trace::Level::error, TAG)
#define MUX_WARNING(TAG) MUX_TRACE(::mux::trace::Level::warning, TAG)
#define MUX_INFO(TAG) MUX_TRACE(::mux::trace::Level::info, TAG)
#define MUX_DEBUG(TAG) MUX_TRACE(::mux::trace::Level::debug, TAG)
#define MUX_VERBOSE(TAG) MUX_TRACE(::mux::trace::Level::verbose, TAG)
