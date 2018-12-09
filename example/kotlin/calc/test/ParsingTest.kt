package calc

import org.junit.Test
import org.junit.jupiter.api.assertThrows
import kotlin.test.assertEquals

class ParserTest {
    @Test fun `add ints`() {
        val parser = Parser()
        parser.add("123+456\n")
        assertEquals(Number(123.0), parser.next())
        assertEquals(Operator(Operation.PLUS), parser.next())
        assertEquals(Number(456.0), parser.next())
        assertEquals(parser.next()!!::class, EndOfExpression::class)
        assertEquals(null, parser.next())
    }

    @Test fun `subtract doubles`() {
        val parser = Parser()
        parser.add("12.3-45.6")
        assertEquals(Number(12.30), parser.next())
        assertEquals(Operator(Operation.MINUS), parser.next())
        assertEquals(null, parser.next())
        parser.add("\n")
        assertEquals(Number(45.60), parser.next())
        assertEquals(parser.next()!!::class, EndOfExpression::class)
        assertEquals(null, parser.next())
    }

    @Test fun `mixed plus minus`() {
        val parser = Parser()
        parser.add("1 + 2 - 1.5 + 2.25\n")
        assertEquals(Number(1.0), parser.next())
        assertEquals(Operator(Operation.PLUS), parser.next())
        assertEquals(Number(2.0), parser.next())
        assertEquals(Operator(Operation.MINUS), parser.next())
        assertEquals(Number(1.5), parser.next())
        assertEquals(Operator(Operation.PLUS), parser.next())
        assertEquals(Number(2.25), parser.next())
        assertEquals(parser.next()!!::class, EndOfExpression::class)
    }

    @Test fun `partial operations`() {
        val parser = Parser()
        parser.add("12*34")
        assertEquals(Number(12.0), parser.next())
        assertEquals(Operator(Operation.MULTIPLY), parser.next())
        assertEquals(null, parser.next())
        parser.add("56/78")
        assertEquals(Number(3456.0), parser.next())
        assertEquals(Operator(Operation.DIVIDE), parser.next())
        assertEquals(null, parser.next())
        parser.add(".7")
        assertEquals(null, parser.next())
        parser.add("2+1\n")
        assertEquals(Number(78.72), parser.next())
        assertEquals(Operator(Operation.PLUS), parser.next())
        assertEquals(Number(1.0), parser.next())
        assertEquals(parser.next()!!::class, EndOfExpression::class)
    }

    @Test fun `brackets`() {
        val parser = Parser()
        parser.add("1+(-2)*3\n")
        assertEquals(Number(1.0), parser.next())
        assertEquals(Operator(Operation.PLUS), parser.next())
        assertEquals(Operator(Operation.OPEN_BRACKET), parser.next())
        assertEquals(Operator(Operation.MINUS), parser.next())
        assertEquals(Number(2.0), parser.next())
        assertEquals(Operator(Operation.CLOSE_BRACKET), parser.next())
        assertEquals(Operator(Operation.MULTIPLY), parser.next())
        assertEquals(Number(3.0), parser.next())
        assertEquals(parser.next()!!::class, EndOfExpression::class)
    }

    @Test fun `with spaces`() {
        val parser = Parser()
        parser.add(" 23.3 + 7/2 3\n")
        assertEquals(Number(23.3), parser.next())
        assertEquals(Operator(Operation.PLUS), parser.next())
        assertEquals(Number(7.0), parser.next())
        assertEquals(Operator(Operation.DIVIDE), parser.next())
        assertEquals(Number(2.0), parser.next())
        assertEquals(Number(3.0), parser.next())
        assertEquals(parser.next()!!::class, EndOfExpression::class)
    }

    @Test fun `unexpected simbols`() {
        assertThrows<SyntaxError> { Parser().add("25 ? 6") }
        assertThrows<SyntaxError> { Parser().add("2 != 2") }
        assertThrows<SyntaxError> { Parser().add("(2 + 3.4]") }
    }

    @Test fun `unexpected format`() {
        val parser = Parser()
        parser.add("6 + 2.7")
        assertThrows<SyntaxError> { parser.add(".8+2") }
    }
}