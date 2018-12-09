package calc

import java.text.DecimalFormat
import java.util.LinkedList
import java.util.logging.Logger

class CalculationError(message: String) : Error(message)

// TODO: This implementation is full of shit! Rewrite it!
class Calculator {
    init { LOGGER.info { "New calculator" } }
    private val _numbers = LinkedList<Double>()
    private var _nextNumberSign = 1.0
    private val _operations = LinkedList<Operation>()
    private var _openedBrackets = 0

    fun add(token: Token) {
        when (token) {
            is Number -> add(token.value)
            is Operator -> add(token.value)
            else -> throw SyntaxError("Unexpected token: $token")
        }
    }

    fun add(number: Double) {
        if (_numbers.size != _operations.size - _openedBrackets)
            throw SyntaxError("Unexpected number: $number")

        val nextNumber = number * _nextNumberSign
        _nextNumberSign = 1.0
        LOGGER.fine { "Add number: $nextNumber" }
        _numbers.push(nextNumber)
        if (lastOperation() in listOf(Operation.MULTIPLY, Operation.DIVIDE))
            executeOne()
    }

    fun add(operator: Operation) {
        when (operator) {
            Operation.OPEN_BRACKET -> {
                if (_numbers.size != _operations.size - _openedBrackets)
                    throw SyntaxError("Unexpected open bracket")

                LOGGER.fine { "Open bracket" }
                _operations.push(Operation.OPEN_BRACKET)
                _openedBrackets += 1
            }
            Operation.CLOSE_BRACKET -> {
                if (_numbers.size == _operations.size - _openedBrackets || _openedBrackets == 0)
                    throw SyntaxError("Unexpected closing bracket")

                executeScope()
                LOGGER.fine { "Remove bracket bracket" }
                assert(_operations.pop() == Operation.OPEN_BRACKET)
                _openedBrackets -= 1
                if (lastOperation() in listOf(Operation.MULTIPLY, Operation.DIVIDE))
                    executeOne()
            }
            else -> {
                if (_numbers.size == _operations.size - _openedBrackets) {
                    if (operator != Operation.MINUS)
                        throw SyntaxError("Unexpected operator: $operator")

                    _nextNumberSign *= -1.0
                    return
                }

                LOGGER.fine { "Add operator: $operator" }
                if (operator == Operation.MINUS) {
                    _operations.push(Operation.PLUS)
                    _nextNumberSign *= -1.0
                }
                else {
                    _operations.push(operator)
                }
            }
        }
    }

    fun result(): String {
        if (_openedBrackets != 0)
            throw SyntaxError("Expected $_openedBrackets closing bracket(s)")

        executeScope()
        assert(_numbers.size == 1)
        assert(_operations.isEmpty())

        val value = _numbers.pop()
        LOGGER.info { "Result: $value" }
        return when(value) {
            Double.POSITIVE_INFINITY -> "Infinity"
            Double.NEGATIVE_INFINITY -> "Negative Infinity"
            Double.NaN -> "Not a Number"
            else -> RESULT_FORMAT.format(value)
        }
    }

    private fun executeOne() {
        val operation = _operations.pop()
        val right = _numbers.pop()
        val left = _numbers.pop()
        val result = when (operation) {
            Operation.PLUS -> left + right
            Operation.MINUS -> left - right
            Operation.MULTIPLY -> left * right
            Operation.DIVIDE -> left / right
            else -> throw CalculationError("Unexpected operation: $operation")
        }

        LOGGER.fine { "$left $operation $right is $result" }
        _numbers.push(result)
    }

    private fun executeScope() {
        LOGGER.fine("Sum up last expression")
        while (_operations.isNotEmpty() && _operations.first != Operation.OPEN_BRACKET)
            executeOne()
    }

    private fun lastOperation(): Operation?
        = if (_operations.isEmpty()) null else _operations.first

    companion object {
        private val LOGGER = Logger.getLogger(this::class.java.toString())
        private val RESULT_FORMAT = DecimalFormat("0.#####")
    }
}

fun calculate(expression: String): String {
    val parser = Parser()
    parser.add(expression + "\n")

    val calculator = Calculator()
    while (true) {
        val token = parser.next()!!
        calculator.add(if (token is EndOfExpression) break else token)
    }

    assert(parser.next() == null)
    return calculator.result()
}