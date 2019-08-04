use std::fmt;
use std::io::{stdin, stdout, Write};
use std::sync::{Arc, Mutex};

use super::compare::{Container, min, max};
use super::stack::Stack;
use super::queue::Queue;


pub struct Cli {
    container: Box<Container<String> + Send>,
}

impl Cli {
    pub fn new(container: Option<&str>, compare: Option<&str>) -> Result<Cli, String> {
        let compare_fn = match compare {
            None | Some("min") => min,
            Some("max") => max,
            Some(name) => return Err(format!("Unsupported compare type: {}", name)),
        };
        return Ok(Cli {
            container: match container {
                None | Some("s") | Some("stack") => Box::new(Stack::new(compare_fn)),
                Some("q") | Some("queue") => Box::new(Queue::new(compare_fn)),
                Some(name) => return Err(format!("Unsupported container type: {}", name)),
            }
        });
    }

    pub fn send(&mut self, input: &str, output: &mut String) -> bool {
        let delimiter = input.find(" ").unwrap_or(input.len());
        let (command, value) = input.split_at(delimiter);
        match command.trim() {
            "help" | "h" | "?" => {
                output.push_str("Commands: in <s>, out, top, extremum, count, quit.");
            },
            "in" | "i" => {
                self.container.push(value.trim().to_string());
                output.push_str("ok");
            },
            "out" | "o" => match self.container.pop() {
                None => output.push_str("<empty>"),
                Some(value) => output.push_str(&value),
            },
            "top" | "t" => match self.container.extremum() {
                None => output.push_str("<empty>"),
                Some(value) => output.push_str(value),
            },
            "extremum" | "e" => match self.container.extremum() {
                None => output.push_str("<empty>"),
                Some(value) => output.push_str(value),
            },
            "count" | "c" => {
                output.push_str(&self.container.len().to_string()[..]);
            },
            "quit" | "q" => {
                return false;
            },
            _ => {
                output.push_str("Unknown command: ");
                output.push_str(command);
            }
        };
        return true;
    }
}

pub fn std_io_loop(cli: &mut Cli) -> std::io::Result<()> {
    println!("Welcome to CLI. Type 'help' or 'h' to see help.");
    let mut read_buffer = String::new();
    let mut write_buffer = String::new();
    loop {
        print!("> ");
        stdout().flush()?;
        stdin().read_line(&mut read_buffer)?;
        if !cli.send(read_buffer[..].trim(), &mut write_buffer) {
            return Ok(())
        }
        println!("{}", write_buffer);
        read_buffer.clear();
        write_buffer.clear();
    }
}

impl fmt::Display for Cli {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.container.name())
    }
}

#[derive(Clone)]
pub struct SyncCli {
    cli: Arc<Mutex<Box<Cli>>>,
}

impl SyncCli {
    pub fn new(cli: Cli) -> SyncCli {
        SyncCli { cli: Arc::new(Mutex::new(Box::new(cli))) }
    }
    pub fn send(&mut self, input: &str, output: &mut String) -> bool {
        self.cli.lock().unwrap().send(input, output)
    }
}

impl fmt::Display for SyncCli {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.cli.lock().unwrap())
    }
}

#[cfg(test)]
mod bad_args {
    use super::*;
    fn expect_error(container: &str, compare: &str, error: &str) {
        match Cli::new(Some(container), Some(compare)) {
            Ok(_) => assert!(false, "should not construct"),
            Err(m) => assert_eq!(m, error),
        }
    }

    #[test]
    fn main() {
        expect_error("wtf", "min", "Unsupported container type: wtf");
        expect_error("s", "wtf", "Unsupported compare type: wtf");
        expect_error("q", "wtf", "Unsupported compare type: wtf");
    }
}

#[cfg(test)]
mod send {
    use super::*;
    fn expect_send<'b>(cli: &mut Cli, message: &str, result: &str) {
        let mut buffer = String::from("");
        cli.send(message, &mut buffer);
        assert_eq!(buffer, result);
    }

    #[test]
    fn stack_min() {
        let mut cli = match Cli::new(Some("stack"), Some("min")) {
            Ok(c) => c,
            Err(m) => { assert!(false, m); return }
        };

        expect_send(&mut cli, "in hello", "ok");
        expect_send(&mut cli, "count", "1");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "hello", "Unknown command: hello");

        expect_send(&mut cli,  "in world", "ok");
        expect_send(&mut cli, "count", "2");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "hello world", "Unknown command: hello");

        expect_send(&mut cli, "out", "world");
        expect_send(&mut cli, "count", "1");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "", "Unknown command: ");

        expect_send(&mut cli, "in bad", "ok");
        expect_send(&mut cli, "count", "2");
        expect_send(&mut cli, "extremum", "bad");
    }

    #[test]
    fn queue_max() {
        let mut cli = match Cli::new(Some("queue"), Some("max")) {
            Ok(c) => c,
            Err(m) => { assert!(false, m); return }
        };

        expect_send(&mut cli, "i hello", "ok");
        expect_send(&mut cli, "c", "1");
        expect_send(&mut cli, "e", "hello");

        expect_send(&mut cli, "i world", "ok");
        expect_send(&mut cli, "c", "2");
        expect_send(&mut cli, "e", "world");

        expect_send(&mut cli, "o", "hello");
        expect_send(&mut cli, "c", "1");
        expect_send(&mut cli, "e", "world");

        expect_send(&mut cli, "o", "world");
        expect_send(&mut cli, "c", "0");
        expect_send(&mut cli, "e", "<empty>");

        expect_send(&mut cli,  "o", "<empty>");
        expect_send(&mut cli, "c", "0");
        expect_send(&mut cli, "e", "<empty>");
    }
}