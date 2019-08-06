package main

import (
	"log"
	"strings"
)

// KvCli provides key-value CLI.
type KvCli struct {
	storage map[string]string
}

// NewKvCli constructs empty key-value CLI.
func NewKvCli() KvCli {
	return KvCli{map[string]string{}}
}

// Greet provides help.
func (cli *KvCli) Greet() string {
	return "Type 'key = value' to set value or 'key' to get value."
}

// Send provides a response to message or nil to finish the session.
func (cli *KvCli) Send(message string) string {
	message = strings.TrimSpace(message)
	if message == "" {
		return ""
	}
	if s := strings.SplitN(message, "=", 2); len(s) == 2 {
		k := strings.TrimSpace(s[0])
		v := strings.TrimSpace(s[1])
		cli.storage[k] = v
		log.Printf("%T set '%v' = '%v'", cli, k, v)
		return "ok"
	}
	k := message
	v := cli.storage[k]
	if v == "" {
		v = "<empty>"
	}
	log.Printf("%T get '%v' = '%v'", cli, k, v)
	return v
}
