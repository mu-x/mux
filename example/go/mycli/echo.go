package main

import "strings"

// EchoCli provides echo CLI.
type EchoCli struct {
}

// Greet provides greeting message.
func (c *EchoCli) Greet() string {
	return "Echo CLI"
}

// Send provides a response to message or nil to finish the session.
func (c *EchoCli) Send(m string) string {
	return strings.TrimSpace(m)
}
