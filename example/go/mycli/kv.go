package main

import (
	"log"
	"strings"
)

// NewKeyValueCli constructs an empty key-value CLI.
func NewKeyValueCli() Cli {
	return &keyValueCli{map[string]string{}}
}

type keyValueCli struct {
	storage map[string]string
}

func (c *keyValueCli) Name() string {
	// return "Type 'key = value' to set value or 'key' to get value."
	return "Key-Value"
}

func (c *keyValueCli) Help() []string {
	return []string{
		"key = value -- set key to value",
		"key         -- returns value for this key",
	}
}

func (c *keyValueCli) Send(message string) *string {
	message = strings.TrimSpace(message)
	if message == "" {
		return nil
	}

	if s := strings.SplitN(message, "=", 2); len(s) == 2 {
		k := strings.TrimSpace(s[0])
		v := strings.TrimSpace(s[1])

		c.storage[k] = v
		log.Printf("%T set '%v' = '%v'", c, k, v)

		okReplay := ""
		return &okReplay
	}

	k := message
	v := c.storage[k]

	log.Printf("%T get '%v' = '%v'", c, k, v)
	return &v
}
