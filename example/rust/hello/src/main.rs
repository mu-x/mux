use std::io::Write;

mod containers;
use containers::ExtremumStack;

fn main() -> std::io::Result<()> {
    let mut stack: ExtremumStack<String> = ExtremumStack::new();
    print_help();
    loop {
        print!("\n> ");
        std::io::stdout().flush()?;
        let mut input = String::new();
        std::io::stdin().read_line(&mut input)?;

        let delimiter = input.find(" ").unwrap_or(input.len() - 1);
        let (command, value) = input.split_at(delimiter);
        match command {
            "push" => stack.push(value.trim().to_string()),
            "pop" => print_value(stack.pop()),
            "extremum" => print_value(stack.extremum()),
            _ => {
                println!("Invalid command");
                print_help();
            }
        }
    }
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
