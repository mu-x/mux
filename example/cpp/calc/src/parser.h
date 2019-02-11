#include <optional>
#include <iostream>

namespace mux::calculator {

enum class Operator {
    plus = '+',
    minus = '-',
    multiply = '*',
    divide = '/',
    open = '(',
    close = ')',
};

inline
std::optional<Operator> makeOperator(char character) {
    const auto value = static_cast<Operator>(character);
    switch (value) {
      case Operator::plus:
      case Operator::minus:
      case Operator::multiply:
      case Operator::divide:
      case Operator::open:
      case Operator::close:
        return value;
    }
    return std::nullopt;
}

inline
std::ostream& operator<<(std::ostream& stream, Operator value)
{
    return stream << static_cast<char>(value);
}

// <--

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::optional<T>& value)
{
    return value ? (stream << *value) : (stream << "nullopt");
}

struct Printable {
    virtual void print(std::ostream* stream) const = 0;
    virtual ~Printable() = default;
};

inline
std::ostream& operator<<(std::ostream& stream, const Printable& value)
{
    value.print(&stream);
    return stream;
}

// -->

struct Token: Printable {
};

struct Operation: Token {
    Operator value;
    virtual void print(std::ostream* stream) const override { *stream << value; }
};

template<typename NumberType>
struct Number: Token {
    NumberType value;
    virtual void print(std::ostream* stream) const override { *stream << value; }
};

template<typename NumberType>
class Parser {
    Parser(std::istream& stream);
    std::unique_ptr<Token> get();
};

} // namespace mux::calculator
