package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	cli := NewKvCli()
	RunStdioCli(&cli)
}

// Cli represents a generic CLI inteface.
type Cli interface {
	Greet() string
	Send(m string) string
}

// RunStdioCli runs cli in stdin and stdout.
func RunStdioCli(cli Cli) {
	reader := bufio.NewReader(os.Stdin)
	if greet := cli.Greet(); greet != "" {
		fmt.Println(greet)
	}
	for {
		fmt.Print("> ")
		request, err := reader.ReadString('\n')
		if err != nil {
			// TODO: Log err.
			return
		}
		response := cli.Send(request)
		if response == "" {
			// TODO: Log connection close by CLI.
			return
		}
		fmt.Println(response)
	}
}
