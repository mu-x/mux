package calc

import org.junit.jupiter.api.assertThrows
import java.util.logging.Level
import org.junit.Test
import kotlin.test.assertEquals

class CalculatorTest {
    init { setLogLevel(Level.FINE) }

    @Test
    fun `flat` () {
        val calculator = Calculator()
        calculator.add(.1)
        assertThrows<SyntaxError> { calculator.add(.2) }
        calculator.add(Operation.PLUS)
        assertThrows<SyntaxError> { calculator.add(Operation.MULTIPLY) }
        calculator.add(.3)
        assertEquals("0.4", calculator.result())
    }

    @Test
    fun `brackets` () {
        val calculator = Calculator()
        calculator.add(1.0)
        assertThrows<SyntaxError> { calculator.add(Operation.OPEN_BRACKET) }
        calculator.add(Operation.MULTIPLY)
        assertThrows<SyntaxError> { calculator.add(Operation.CLOSE_BRACKET) }
        calculator.add(Operation.OPEN_BRACKET)
        assertThrows<SyntaxError> { calculator.add(Operation.DIVIDE) }
        calculator.add(2.0)
        calculator.add(Operation.MINUS)
        assertThrows<SyntaxError> { calculator.add(Operation.PLUS) }
        calculator.add(1.0)
        calculator.add(Operation.CLOSE_BRACKET)
        assertEquals("1", calculator.result())
    }
}

class CalcuclateTest {
    init { setLogLevel(Level.FINE) }

    companion object {
        fun success(result: String, expression: String)
            = assertEquals(result, calculate(expression))

        inline fun <reified T: Throwable> error(expression: String) {
            assertThrows<T> { calculate(expression) }
        }
    }

    @Test fun `sum positive`() = success("6.1", "1 + 2 + 3.1")
    @Test fun `sum mixed`() = success("3.75", "1 + 2 - 1.5 + 2.25")
    @Test fun `priorities`() = success("8", "2 + 7 * 2 - 8")
    @Test fun `brackets`() = success("-54", "(2 + 7) * (2 - 8)")
    @Test fun `negative numbers`() = success("-7.5", "5 * (-0.1) + -7")
    @Test fun `devision by zero`() = success("Infinity", "7 / (1 + 2 - 3)")

    @Test fun `wrong double`() = error<SyntaxError>("2.7 / 5.5.3")
    @Test fun `wrong symbols`() = error<SyntaxError>("i + 2")
    @Test fun `wrong format`() = error<SyntaxError>("1 + 2 3 * 5")
    @Test fun `double operators`() = error<SyntaxError>("2 +/ 3")
    @Test fun `non-closing brackets`() = error<SyntaxError>("(1 + 5 * (2 - 3)")
    @Test fun `extra brackets`() = error<SyntaxError>("5 * (2 - 3) + 2)")
}