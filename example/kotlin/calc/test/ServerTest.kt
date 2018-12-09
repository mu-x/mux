package calc

import junit.framework.TestCase
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.junit.Test
import java.io.DataInputStream
import java.io.DataOutputStream
import java.net.Socket
import java.net.SocketAddress
import java.util.logging.Level

class Client(private val _address: SocketAddress) : AutoCloseable {
    private val _client = Socket().apply {
        soTimeout = 1000 //< 1 second should be more than enough.
        connect(_address)
    }

    private val _sender = DataOutputStream(_client.getOutputStream())
    private val _receiver = DataInputStream(_client.getInputStream())

    override fun close() = _client.close()

    fun communicate(string: String, autoComplete: Boolean = true): String {
        var request = if (autoComplete) string + '\n' else string
        _sender.write(request.toByteArray())

        var response = ""
        while (!response.endsWith('\n'))
            response += _receiver.read().toChar()
        return response.substring(0, response.length - 1)
    }
}

class CalculatorServerTest : TestCase() {
    private val _server = CalculatorServer()
    private val _routine = GlobalScope.launch { _server.run() }
    init { setLogLevel(Level.INFO)}

    override fun tearDown() {
        super.tearDown()
        runBlocking { _routine.cancel() }
    }

    fun `test correct expressions`() = Client(_server.address).use { client ->
        assertEquals("4", client.communicate("2 + 2"))
        assertEquals("Negative Infinity", client.communicate("-100 / 0"))
        assertEquals("2", client.communicate("2 * 2 + 7 - (3 * 3)"))
    }

    fun `test expect errors`() = Client(_server.address).use { client ->
        assertEquals("2", client.communicate("1 + 1"))
        assertEquals("Error: Unexpected operator: e", client.communicate("error"))
        assertEquals("0", client.communicate("2 - 2"))
        assertEquals("Error: Expected 1 closing bracket(s)", client.communicate("(1 + "))
        assertEquals("9", client.communicate("3 * 3"))
        assertEquals("Error: Unable to parse number '4.0.0': multiple points",
            client.communicate("(1 + 4.0.0) * 8"))
        assertEquals("1", client.communicate("4 / 4"))
    }

    fun `test batch queries`() = Client(_server.address).use { client ->
        assertEquals("2", client.communicate("1+1 \n 2-2 \n 3*3 \n 9", autoComplete = false))
        assertEquals("0", client.communicate("", autoComplete = false))
        assertEquals("9", client.communicate("", autoComplete = false))
        assertEquals("1", client.communicate("/ 9"))
    }

    @Test fun `2 clients`() = Client(_server.address).use { client1 ->
        assertEquals("4", client1.communicate("2 + 2"))
        Client(_server.address).use { client2 ->
            assertEquals("2", client2.communicate("2 * 2 + 7 - (3 * 3)"))
            assertEquals("36", client2.communicate("6 * 6"))
            assertEquals("Error: Unexpected operator: e", client1.communicate("error"))
        }
    }
}