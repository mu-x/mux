use std::env::args;

mod cli;
mod compare;
mod server;
mod stack;
mod queue;

use cli::{Cli, std_io_loop};
use server::{run_local_server};

fn main() -> std::io::Result<()> {
    // TODO: Use some kind of argument parser and convenient error handling.
    let mut cli = match Cli::new(
        args().nth(1).as_ref().map(|s| s.as_str()),
        args().nth(2).as_ref().map(|s| s.as_str()),
    ) {
        Ok(c) => c,
        Err(message) => {
            println!("Error: {}", message);
            return Ok(());
        },
    };
    match args().nth(3).map(|s| s.parse::<u16>()) {
        None => std_io_loop(&mut cli),
        Some(port) => match port {
            Ok(p) => run_local_server(cli, p),
            Err(_) => { println!("Error: Invalid port"); Ok(()) },
        },
    }
}
