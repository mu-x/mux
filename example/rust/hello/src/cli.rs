use std::io::{stdin, stdout, Write};

use super::compare::{InOut, min, max};
use super::stack::ExtremumStack as Stack;
use super::queue::ExtremumQueue as Queue;

pub struct Cli {
    container: Box<InOut<String>>,
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

    pub fn send(&mut self, input: &str, output: &mut String) {
        let delimiter = input.find(" ").unwrap_or(input.len());
        let (command, value) = input.split_at(delimiter);
        match command.trim() {
            "push" => {
                self.container.push(value.trim().to_string());
                output.push_str("ok");
            },
            "pop" => match self.container.pop() {
                None => output.push_str("<empty>"),
                Some(value) => output.push_str(&value),
            },
            "extremum" => match self.container.extremum() {
                None => output.push_str("<empty>"),
                Some(value) => output.push_str(value),
            },
            "len" => {
                output.push_str(&self.container.len().to_string()[..]);
            },
            _ => {
                output.push_str("Unknown command: ");
                output.push_str(command);
            }
        };
    }
}

pub fn std_io_loop(cli: &mut Cli) -> std::io::Result<()> {
    let mut read_buffer = String::new();
    let mut write_buffer = String::new();
    loop {
        stdin().read_line(&mut read_buffer)?;
        cli.send(read_buffer[..].trim(), &mut write_buffer);

        println!("{}", write_buffer);
        stdout().flush()?;

        read_buffer.clear();
        write_buffer.clear();
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

        expect_send(&mut cli, "push hello", "ok");
        expect_send(&mut cli, "len", "1");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "hello", "Unknown command: hello");

        expect_send(&mut cli,  "push world", "ok");
        expect_send(&mut cli, "len", "2");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "hello world", "Unknown command: hello");

        expect_send(&mut cli, "pop", "world");
        expect_send(&mut cli, "len", "1");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "", "Unknown command: ");

        expect_send(&mut cli, "push bad", "ok");
        expect_send(&mut cli, "len", "2");
        expect_send(&mut cli, "extremum", "bad");
    }

    #[test]
    fn queue_max() {
        let mut cli = match Cli::new(Some("queue"), Some("max")) {
            Ok(c) => c,
            Err(m) => { assert!(false, m); return }
        };

        expect_send(&mut cli, "push hello", "ok");
        expect_send(&mut cli, "len", "1");
        expect_send(&mut cli, "extremum", "hello");

        expect_send(&mut cli, "push world", "ok");
        expect_send(&mut cli, "len", "2");
        expect_send(&mut cli, "extremum", "world");

        expect_send(&mut cli, "pop", "hello");
        expect_send(&mut cli, "len", "1");
        expect_send(&mut cli, "extremum", "world");

        expect_send(&mut cli, "pop", "world");
        expect_send(&mut cli, "len", "0");
        expect_send(&mut cli, "extremum", "<empty>");

        expect_send(&mut cli,  "pop", "<empty>");
        expect_send(&mut cli, "len", "0");
        expect_send(&mut cli, "extremum", "<empty>");
    }
}
