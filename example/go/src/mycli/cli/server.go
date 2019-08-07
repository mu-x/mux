package mycli

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strings"
)

// Server represents TCP server.
type Server struct {
	cli      Cli
	listener net.Listener
}

// NewServer creates the server.
func NewServer(cli Cli, addr string) (*Server, error) {
	listener, err := net.Listen("tcp", addr)
	if err != nil {
		return nil, err
	}
	return &Server{NewSyncCli(cli), listener}, nil
}

// Close stops the server.
func (server *Server) Close() {
	server.listener.Close()
}

// Address of the server.
func (server *Server) Address() string {
	return server.listener.Addr().String()
}

// Run accepts and serves connections.
func (server *Server) Run() error {
	for {
		conn, err := server.listener.Accept()
		if err != nil {
			return err
		}

		id := conn.RemoteAddr().String()
		go func() {
			log.Println("Client", id, "connected")
			r := Communicate(server.cli, bufio.NewReader(conn), bufio.NewWriter(conn))
			log.Println("Client", id, "disconnected:", r)
		}()
	}
}

// Communicate communicates with cli.
func Communicate(cli Cli, reader *bufio.Reader, writer *bufio.Writer) error {
	greet := fmt.Sprintf("\nWelcome to %v CLI!\n", cli.Name())
	if _, err := writer.WriteString(greet); err != nil {
		return err
	}

	if help := cli.Help(); len(help) > 0 {
		message := fmt.Sprintf("Help:\n  %v\n", strings.Join(help, "\n  "))
		if _, err := writer.WriteString(message); err != nil {
			return err
		}
	}

	for {
		if _, err := writer.WriteString("> "); err != nil {
			return err
		}

		writer.Flush()
		request, err := reader.ReadString('\n')
		if err != nil {
			return err
		}

		response := cli.Send(strings.TrimSpace(request))
		if response == nil {
			return nil //< Disconnect by client request.
		}

		if *response != "" {
			if _, err := writer.WriteString(*response + "\n"); err != nil {
				return err
			}
		}
	}
}
