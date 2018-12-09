package calc

import java.util.LinkedList

const val DEFAULT_EOF = '\n'

enum class Operation {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OPEN_BRACKET,
    CLOSE_BRACKET
}

sealed class Token
data class Number(val value: Double) : Token()
data class Operator(val value: Operation) : Token()
class EndOfExpression : Token()

class SyntaxError(message: String) : Error(message)

fun number(string: String): Number {
    try {
        return Number(string.toDouble())
    } catch (error: NumberFormatException) {
        throw SyntaxError("Unable to parse number '$string': ${error.message}")
    }
}

fun operation(char: Char): Operator {
    return Operator(when (char) {
        '+' -> Operation.PLUS
        '-' -> Operation.MINUS
        '*' -> Operation.MULTIPLY
        '/' -> Operation.DIVIDE
        '(' -> Operation.OPEN_BRACKET
        ')' -> Operation.CLOSE_BRACKET
        else -> throw SyntaxError("Unexpected operator: $char")
    })
}

class Parser(val eof: Char = DEFAULT_EOF) {
    private var _digits = "" //< TODO: Use string builder for better performance.
    private var _parsed = LinkedList<Token>()

    fun add(string: String) = string.forEach { char -> add(char) }

    fun add(char: Char) {
        if (char.isDigit() || char == '.') {
            _digits += char
            return
        }

        if (_digits.isNotEmpty())
            _parsed.push(number(_digits)).also { _digits = "" }

        if (char == this.eof)
            _parsed.push(EndOfExpression())
        else if (!char.isWhitespace())
            _parsed.push(operation(char))
    }

    fun next(): Token? = if (_parsed.isNotEmpty()) _parsed.pollLast() else null
}