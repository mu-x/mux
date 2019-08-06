package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestKvGreet(test *testing.T) {
	cli := NewKvCli()
	assert.Equal(test, "Type 'key = value' to set value or 'key' to get value.", cli.Greet())
}

func TestKvSend(test *testing.T) {
	cli := NewKvCli()
	for _, t := range []struct{ in, out string }{
		{"a = 1", "ok"},
		{"a", "1"},
		{"b", "<empty>"},
		{"c = ", "ok"},
		{"c", ""},
	} {
		assert.Equal(test, t.out, cli.Send(t.in))
	}
}
