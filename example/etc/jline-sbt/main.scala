import scala.tools.jline.console.ConsoleReader
import scala.tools.jline.console.completer._

object Main {
    def main(args: Array[String]) {
        var r = new ConsoleReader
        r addCompleter new FileNameCompleter
        r addCompleter new StringsCompleter("foo", "bar", "baz")
        r setPrompt "> "

        var line = new String
        while ((line = r.readLine()) != null)
            println(s"< $line")
    }
}
