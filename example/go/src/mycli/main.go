package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"log"
	"os"

	mycli "mycli/cli"
)

func main() {
	opts, err := parseOptions()
	if err != nil {
		fmt.Print(err)
		return
	}

	if opts.verbose {
		log.SetOutput(os.Stderr)
	} else {
		log.SetOutput(ioutil.Discard)
	}

	if opts.address == "" {
		r := mycli.Communicate(opts.cli, bufio.NewReader(os.Stdin), bufio.NewWriter(os.Stdout))
		fmt.Print(r)
		return
	}

	server, err := mycli.NewServer(opts.cli, opts.address)
	if err != nil {
		fmt.Println("Unable to start server on", opts.address, "-", err)
		return
	}
	defer server.Close()

	fmt.Println("Server has started on", server.Address())
	result := server.Run()
	fmt.Println("Server has stopped:", result)
}

type options struct {
	cli     mycli.Cli
	address string
	verbose bool
}

func parseOptions() (options, error) {
	app, args := os.Args[0], os.Args[1:]
	opts := options{}
	for ; len(args) > 0; args = args[1:] {
		arg := args[0]
		switch arg {
		case "-h":
			return opts, fmt.Errorf("Usage: %v [-v] [-s address:port] [echo|kv]", app)
		case "-v":
			opts.verbose = true
		case "-s":
			opts.address = args[1]
			args = args[1:]
		case "echo":
			opts.cli = mycli.NewEchoCli()
		case "kv":
			opts.cli = mycli.NewKeyValueCli()
		default:
			return opts, fmt.Errorf("Error: wrong arg '%v', try -h", arg)
		}
	}
	if len(args) > 0 {
		return opts, fmt.Errorf("Error: wrong args %v, try -h", args)
	}
	if opts.cli == nil {
		opts.cli = mycli.NewEchoCli()
	}
	return opts, nil
}
