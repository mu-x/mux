use std::io;

mod compare;
use compare::{Compare, InOut, min, max};

mod stack;
use stack::ExtremumStack as Stack;

mod queue;
use queue::ExtremumQueue as Queue;

fn main() -> Result<(), String> {
    let args: Vec<String> = std::env::args().collect();
    let mut container = make_container(
        args.get(1).unwrap_or(&"queue".to_string()),
        args.get(2).unwrap_or(&"max".to_string())
    )?;
    print_help();
    loop {
        let input = match read_line() {
            Ok(input) => input,
            Err(_) => return Err("Input stream is terminated".to_string()),
        };
        let delimiter = input.find(" ").unwrap_or(input.len() - 1);
        let (command, value) = input.split_at(delimiter);
        match command {
            "push" => container.push(value.trim().to_string()),
            "pop" => print_value(container.pop()),
            "extremum" => print_value(container.extremum()),
            _ => {
                println!("Invalid command");
                print_help();
            }
        }
    }
}

fn read_line() -> io::Result<String> {
    use std::io::Write;
    print!("\n> ");
    io::stdout().flush()?;
    let mut input = String::new();
    io::stdin().read_line(&mut input)?;
    return Ok(input);
}

fn make_compare(extremum: &str) -> Result<Compare<String>, String> {
    return match extremum {
        "min" => Ok(min),
        "max" => Ok(max),
        _ => Err(format!("Unsupported extremum: {}", extremum)),
    };
}

fn make_container(name: &str, extremum: &str) -> Result<Box<InOut<String>>, String> {
    let compare = make_compare(extremum)?;
    return match name {
        "s" | "stack" => Ok(Box::new(Stack::new(compare))),
        "q" | "queue" => Ok(Box::new(Queue::new(compare))),
        _ => Err(format!("Unsupported type: {}", name)),
    };
}

fn print_help() {
    println!("Supported commands:");
    println!("  push <string>");
    println!("  pop <string>");
    println!("  extremum <string>");
}

fn print_value<T: std::fmt::Display>(value: Option<T>) {
    match value {
        None => println!("Empty!"),
        Some(value) => println!("Value: {}", value),
    }
}
