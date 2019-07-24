use std::env::args;

mod cli;
mod compare;
mod stack;
mod queue;

use cli::{Cli, std_io_loop};

fn main() -> std::io::Result<()> {
    let mut cli = match Cli::new(
        args().nth(1).as_ref().map(|s| s.as_str()),
        args().nth(2).as_ref().map(|s| s.as_str())
    ) {
        Ok(c) => c,
        Err(message) => {
            println!("Error: {}", message);
            return Ok(());
        },
    };
    return std_io_loop(&mut cli);
}
