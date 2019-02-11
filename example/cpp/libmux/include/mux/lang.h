#pragma once

#include <stdexcept>
#include <string>

namespace mux {

/**
 * RAII based scope guard.
 * 
 * Usage:
 * ```
 *   mutex.lock();
 *   mux::ScopeGuard lockGuard([]{ mutex.unlock(); });
 *   doStuff();
 * ``` 
 * 
 * Equivalent of:
 * ```
 *   mutex.lock();
 *   doStuff();
 *   mutex.unlock();
 * ```
 * 
 * But exception safe and allows several returns.
 */
template<typename Function>
class ScopeGuard
{
public:
    ScopeGuard(Function function): function_(std::move(function)) {}
    ~ScopeGuard() { function_(); }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&&) = delete;

    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;

private:
    Function function_;
};

template<typename Function>
ScopeGuard<Function> scopeGuard(Function function) 
{ 
    return ScopeGuard<Function>(std::move(function)); 
}

struct Default {} default_;

template<typename Value, typename Action>
auto switch_(const Value&, const Default&, const Action& defaultAction)
    -> decltype(defaultAction())
{
    return defaultAction();
}

/**
 * The switch statement for any types and return values.
 * 
 * Usage:
 * ```
 *  const std::string line = mux::switch_(
 *      count,
 *      0, []{ return "none"; },
 *      1, []{ return "single"; },
 *      mux::default_, []{ return "many"; }
 *  ); 
 * ```
 * 
 * Equivalent of:
 * ```
 * std::string line;
 * switch (count)
 * {
 *     case 0: line = "none";
 *     case 1: line = "single";
 *     default: line = "many";
 * }
 * 
 * But keeps `line` const and supports `count` of any type.
 * ```
 */
template<typename Value, typename Match, typename Action, typename... Tail>
auto switch_(const Value& value, const Match& match, const Action& action,
    Tail... tail) -> decltype(action())
{
    if (value == match)
        return action();

    if constexpr (sizeof...(tail) > 0)
        return switch_(value, std::forward<Tail>(tail)...);
        
    throw std::logic_error("Unexpected value");
}

} // namespace mux

/**
 * Enum safe switch, asserts if non of the cases is selected.
 * 
 * Usage:
 * ```
 * // Asserts if `value == Enum::value3` or contains some other garbage.
 * const std::string& string = MUX_SWITCH(value,
 * {
 *     case Enum::value1: return "value1";  
 *     case Enum::value2: return "value2";  
 * });
 * ``` 
 */
#define MUX_ENUM_SWITCH(VALUE, BODY) ([&] { \
    const auto mux_enum_switch_value_ = (VALUE); \
    switch(mux_enum_switch_value_) \
    BODY \
    throw std::logic_error("Unexpected enum value: " + std::to_string( \
        static_cast<int>(mux_enum_switch_value_))); \
}())
