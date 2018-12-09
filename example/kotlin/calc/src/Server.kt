package calc

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.net.InetSocketAddress
import java.net.SocketAddress
import java.nio.ByteBuffer
import java.util.logging.Logger
import java.nio.channels.AsynchronousServerSocketChannel
import java.nio.channels.AsynchronousSocketChannel
import java.util.LinkedList
import kotlin.coroutines.resume
import kotlin.coroutines.resumeWithException
import kotlin.coroutines.suspendCoroutine

const val DEFAULT_PORT = 0
const val DEFAULT_BUFFER_SIZE = 10 * 1024 * 1024 //< 10 MB.

class ServerError(message: String) : Error(message)

class Acceptor(port: Int = DEFAULT_PORT) : AutoCloseable {
    private val _acceptor: AsynchronousServerSocketChannel = {
        try {
            AsynchronousServerSocketChannel.open().bind(InetSocketAddress("0.0.0.0", port))
        } catch (error: Throwable) {
            throw ServerError(error.message ?: "Unknown $(error)")
        }
    }()

    val address: SocketAddress = _acceptor.localAddress

    override fun close() = _acceptor.close()

    suspend fun accept() = suspendCoroutine<Connection> { continuation ->
        _acceptor.accept(null, object :
            java.nio.channels.CompletionHandler<AsynchronousSocketChannel, Nothing?>
        {
            override fun completed(channel: AsynchronousSocketChannel, attachment: Nothing?) {
                continuation.resume(Connection(channel))
            }
            override fun failed(exception: Throwable, attachment: Nothing?) {
                continuation.resumeWithException(ServerError(exception.message!!))
            }
        })
    }

    class Connection(private val _channel: AsynchronousSocketChannel) : AutoCloseable {
        val address: SocketAddress
            = _channel.remoteAddress ?: throw ServerError("Failed to get channel port")

        override fun close() = _channel.close()

        suspend fun read(buffer: ByteBuffer): Int = suspendCoroutine { continuation ->
            _channel.read(buffer, Unit, object: java.nio.channels.CompletionHandler<Int, Unit> {
                override fun completed(bytes: Int, attachment: Unit) {
                    _logger.fine { "Got $bytes bytes from $address" }
                    continuation.resume(bytes)
                }
                override fun failed(exception: Throwable, attachment: Unit) {
                    _logger.fine { "Error '${exception.message}' from $address" }
                    continuation.resumeWithException(ServerError(exception.message!!))
                }
            })
        }

        suspend fun write(buffer: ByteBuffer): Int = suspendCoroutine { continuation ->
            _channel.write(buffer, Unit, object: java.nio.channels.CompletionHandler<Int, Unit> {
                override fun completed(bytes: Int, attachment: Unit) {
                    _logger.fine { "Sent $bytes bytes to $address" }
                    continuation.resume(bytes)
                }
                override fun failed(exception: Throwable, attachment: Unit) {
                    _logger.fine { "Error '${exception.message}' from $address" }
                    continuation.resumeWithException(ServerError(exception.message!!))
                }
            })
        }
    }

    companion object {
        private var _logger = Logger.getLogger(this::class.java.toString())
    }
}

class CalculatorStream(eof: Char = DEFAULT_EOF) {
    private var _parser = Parser(eof)
    private var _calculator = Calculator()
    private var _dropToEof = false
    private var _results = LinkedList<String>()

    fun put(buffer: ByteBuffer) {
        for (i in 0..buffer.position() - 1) {
            val char = buffer.get(i).toChar()
            if (_dropToEof) {
                _dropToEof = char != _parser.eof
                continue
            }
            try {
                parse(buffer.get(i).toChar())
            } catch (error: SyntaxError) {
                _results.push("Error: ${error.message}")
                _parser = Parser()
                _calculator = Calculator()
                if (char != _parser.eof)
                    _dropToEof = true
            }
        }
    }

    fun get(buffer: ByteBuffer) {
        while (true) {
            var result = if (_results.isNotEmpty()) _results.last() else return
            var bytes = (result + '\n').toByteArray()
            buffer.put(if (bytes.size <= buffer.remaining()) bytes else return)
            _results.pollLast()
        }
    }

    private fun parse(char: Char) {
        _parser.add(char)
        while (true) {
            val token = _parser.next()
            when (token) {
                is EndOfExpression -> {
                    _results.push(_calculator.result())
                    _calculator = Calculator()
                }
                null -> return
                else -> _calculator.add(token)
            }
        }
    }
}

class CalculatorServer(
    port: Int = DEFAULT_PORT,
    val bufferSize: Int = DEFAULT_BUFFER_SIZE,
    val eof: Char = DEFAULT_EOF
): AutoCloseable {
    private val _server = Acceptor(port)

    val address = _server.address
    override fun close() = _server.close()

    suspend fun run() {
        while (true) {
            val connection = _server.accept()
            GlobalScope.launch { communicate(connection) } // TODO: Wait on it at some point?
        }
    }

    private suspend fun communicate(connection: Acceptor.Connection) = connection.use {
        LOGGER.info { "New connection from ${connection.address}" }
        val buffer = ByteBuffer.allocate(bufferSize)
        val calculator = CalculatorStream(eof)
        while (true) {
            connection.read(buffer)
            calculator.put(if (buffer.position() > 0) buffer else break)
            buffer.clear()
            calculator.get(buffer)
            buffer.flip()
            connection.write(buffer)
            buffer.clear()
        }
        LOGGER.info { "Disconnected from ${connection.address}" }
    }

    companion object {
        private var LOGGER = Logger.getLogger(this::class.java.toString())
    }
}