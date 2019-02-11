#include <mux/lang.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace mux {
namespace tests {

TEST_CASE("ScopeGuard")
{
    int counter = 0;
    {
        const auto guard = mux::scopeGuard([&]{ counter++; });
        REQUIRE(counter == 0);
    }
    REQUIRE(counter == 1);
    {
        const auto guard = mux::scopeGuard([&]{ counter = 17; });
        REQUIRE(counter == 1);
    }
    REQUIRE(counter == 17);
}

std::string voice(const std::string& animal)
{
    return switch_(animal,
        "cat", []{ return "mew"; },
        "dog", []{ return "wof"; },
        default_, []{ return "unknown"; }
    );
}

TEST_CASE("string to string wit default", "switch_")
{
    REQUIRE(voice("cat") == "mew");
    REQUIRE(voice("dog") == "wof");
    REQUIRE(voice("parrot") == "unknown");
    REQUIRE(voice("mouse") == "unknown");
}

enum class Type { a, b };

Type parseType(const std::string& value)
{
    return switch_(value,
        "a", []{ return Type::a; },
        "b", []{ return Type::b; }
    );
}

TEST_CASE("string to enum with exception", "switch_")
{
    REQUIRE(parseType("a") == Type::a);
    REQUIRE(parseType("b") == Type::b);
    REQUIRE_THROWS_AS(parseType("c"), std::logic_error);
    REQUIRE_THROWS_AS(parseType("d"), std::logic_error);
}

std::string toString(Type value)
{
    return MUX_ENUM_SWITCH(value,
    {
        case Type::a: return "a";
        case Type::b: return "b";
    });
}

TEST_CASE("enum to string with exception", "ENUM_SWITCH")
{
    REQUIRE(toString(Type::a) == "a");
    REQUIRE(toString(Type::b) == "b");
    REQUIRE_THROWS_AS(toString(static_cast<Type>(42)), std::logic_error);
    REQUIRE_THROWS_AS(toString(static_cast<Type>(7777)), std::logic_error);
}

} // namespace tests
} // namesapce mux