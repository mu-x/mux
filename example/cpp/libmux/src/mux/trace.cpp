#include <mux/trace.h>

#include <atomic>
#include <ctime>
#include <iostream>
#include <mutex>

namespace mux {
namespace trace {

std::ostream& operator<<(std::ostream& stream, Level value)
{
    // TODO: Use MUX_ENUM_SWITCH.
    switch (value)
    {
        case Level::disabled: return stream << "DISABLED";
        case Level::error: return stream << "ERROR";
        case Level::warning: return stream << "WARNING";
        case Level::info: return stream << "INFO";
        case Level::debug: return stream << "DEBUG";
        case Level::verbose: return stream << "VERBOSE";
    }
    
    // TODO: assert???
    return stream << "LEVEL(" << static_cast<int>(value) << ")";
}

static std::atomic<Level> gLevel;
static std::mutex gMutex;
static std::ostream* gStream(&std::cerr);

Level getLevel()
{
    return gLevel;
}

void setLevel(Level value)
{
    gLevel = value;
}

std::ostream* getStream()
{
    std::lock_guard<std::mutex> lock(gMutex);
    return gStream;
}

void setStream(std::ostream* stream)
{
    std::lock_guard<std::mutex> lock(gMutex);
    gStream = stream;
}

Stream::Stream(Level level, std::string tag, const char* delimiter)
    : level_(level)
    , tag_(std::move(tag))
    , delimiter_(delimiter)
{
    if (delimiter_[0] == 0)
        stream_ << ' ';
}

Stream::~Stream()
{
    if (level_ > getLevel())
        return;
        
    // TODO: Add fractions of seconds.
    static const auto kIsoTimeSize = sizeof("0000-00-00 00:00:00Z");
    static const auto kIsoTimeFormat = "%Y-%m-%d %H:%M:%SZ";
     
    std::time_t currentTime = std::time(nullptr);
    char timeString[kIsoTimeSize];
    strftime(timeString, kIsoTimeSize, kIsoTimeFormat, gmtime(&currentTime));
        
    std::lock_guard<std::mutex> lock(gMutex);
    *gStream << timeString << std::setw(10) << level_
        << ' ' << tag_ << stream_.str(); //< TODO: use std::stringbuf to speedup
}

} // namespace trace
} // namespace mux