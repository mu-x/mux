package calc

import kotlinx.coroutines.runBlocking
import java.util.logging.Level
import java.util.logging.Logger

fun setLogLevel(level: Level = Level.INFO) {
    val mainLogger = Logger.getLogger("")
    mainLogger.level = level
    for (handler in mainLogger.handlers)
        handler.level = level
}

fun main(args: Array<String>) {
    setLogLevel(Level.WARNING)
    when(args.size) {
        0 -> {
            println("Enter expression to see results:")
            while(true) {
                print("> ")
                try {
                    println(calculate(readLine() ?: return))
                } catch (error: SyntaxError) {
                    println("Error: ${error.message}")
                }
            }
        }
        1 -> {
            if (args[0] in listOf("-h", "--help"))
                return print("""
                    calculator          -- cli mode
                    calculator [PORT]   -- server mode
                """.trimIndent())

            try {
                val server = CalculatorServer(args[0].toInt())
                println("Running server on ${server.address}")
                runBlocking { server.use { server.run() } }
            } catch (error: ServerError) {
                println("Error: ${error.message}, see --help")
            }
        }
        else -> {
            println("Error: wring usage, see --help")
        }
    }
}