use std::vec::Vec;
use std::str;
use std::io;
use std::io::prelude::{Read, Write};
use std::fmt;
use std::net::{TcpListener, TcpStream, SocketAddr, IpAddr, Ipv4Addr};

use super::cli::Cli;

const MESSAGE_DELIMITER: &str = "\n";
const MAX_MESSAGE_SIZE: usize = 1024;

#[derive(Debug)]
pub struct Server {
    listener: TcpListener,
    address: SocketAddr,
    cli: Cli,
}

#[allow(dead_code)]
impl Server {
    pub fn new(cli: Cli, bind_address: SocketAddr) -> io::Result<Server> {
        let listener = TcpListener::bind(bind_address)?;
        let address = listener.local_addr()?;
        Ok(Server{ listener, address, cli })
    }

    pub fn address(&self) -> SocketAddr { self.address }

    pub fn run(&mut self) -> io::Result<()> {
        for stream in self.listener.incoming() {
            let mut client = Client::new(stream, &mut self.cli)?;
            println!("Connected client: {}", client);
            client.serve()?; //< TODO: Implement async work with clients.
            println!("Disconnected client: {}", client);
        };
        Ok(())
    }
}

pub fn run_local_server(cli: Cli, port: u16) -> std::io::Result<()> {
    let localhost = IpAddr::from(Ipv4Addr::LOCALHOST);
    let mut server = Server::new(cli, SocketAddr::new(localhost, port))?;
    println!("Server has started: {}", server);
    return server.run();
}

impl fmt::Display for Server {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.address)
    }
}

#[derive(Debug)]
struct Client<'c> {
    stream: TcpStream,
    local_address: SocketAddr,
    remote_address: SocketAddr,
    cli: &'c mut Cli,
}

#[allow(dead_code)]
impl<'c> Client<'c> {
    pub fn new(result: io::Result<TcpStream>, cli: &'c mut Cli) -> io::Result<Client> {
        let stream = result?;
        let local_address = stream.local_addr()?;
        let remote_address = stream.peer_addr()?;
        Ok(Client { stream, local_address, remote_address, cli })
    }

    pub fn local_address(&self) -> SocketAddr { self.local_address }
    pub fn remote_address(&self) -> SocketAddr { self.remote_address }

    pub fn serve(&mut self) -> io::Result<()> {
        // This function should be refactored to replace manual stream parsing.
        let mut read_buffer: Vec::<u8> = vec![0; MAX_MESSAGE_SIZE];
        let mut read_content: usize = 0;
        let mut write_buffer = String::new();
        loop {
            match self.stream.read(&mut read_buffer[read_content..])? {
                0 => return Ok(()), //< Client has closed connection.
                size => {
                    println!("Got message size {} from {}", size, self);
                    read_content += size;
                },
            };
            loop {
                let parse_buffer = match str::from_utf8(&read_buffer[..read_content]) {
                    Ok(s) => s,
                    Err(_) => return Err(io::Error::from(io::ErrorKind::InvalidData)),
                };
                let end = match parse_buffer.find(MESSAGE_DELIMITER) {
                    None => break, //< Continue reading.
                    Some(index) => index,
                };
                if !self.cli.send(&parse_buffer[..end], &mut write_buffer) {
                    return Ok(()) //< Close connection.
                }
                let parsed = end + MESSAGE_DELIMITER.len();
                read_buffer.drain(0..parsed);
                read_buffer.resize(MAX_MESSAGE_SIZE, 0);
                read_content -= parsed;

                write_buffer.push_str(MESSAGE_DELIMITER);
                println!("Send message size {} to {}", write_buffer.len(), self);
                self.stream.write(write_buffer.as_bytes())?;
                write_buffer.clear();
            }
        }
    }
}

impl<'c> fmt::Display for Client<'c> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} <- {}", self.local_address, self.remote_address)
    }
}