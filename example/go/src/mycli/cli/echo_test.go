package mycli

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestEchoCli(test *testing.T) {
	cli := NewEchoCli()
	assert.Equal(test, "Echo", cli.Name())

	for _, t := range []struct{ in, out string }{
		{"hello", "hello"},
		{"hello world", "hello world"},
		{" hello cruel world! ", " hello cruel world! "},
		{"", ""},
	} {
		assert.Equal(test, t.out, *cli.Send(t.in))
	}
}
