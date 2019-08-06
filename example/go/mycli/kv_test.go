package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestKeyValue(test *testing.T) {
	cli := NewKeyValueCli()
	assert.Equal(test, "Key-Value", cli.Name())

	for _, t := range []struct{ in, out string }{
		{"a = 1", ""},
		{"a", "1"},
		{"b", ""},
		{"c = ", ""},
		{"c", ""},
	} {
		assert.Equal(test, t.out, *cli.Send(t.in))
	}

	if cli.Send("") != nil {
		assert.Fail(test, "Connecton did not close in time")
	}
}
