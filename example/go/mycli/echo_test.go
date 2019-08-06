package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestEchoGreet(test *testing.T) {
	cli := EchoCli{}
	assert.Equal(test, "Echo CLI", cli.Greet())
}

func TestEchoSend(test *testing.T) {
	cli := EchoCli{}
	for _, t := range []struct{ in, out string }{
		{"hello", "hello"},
		{"hello world", "hello world"},
		{" hello cruel world! ", "hello cruel world!"},
	} {
		assert.Equal(test, t.out, cli.Send(t.in))
	}
}
