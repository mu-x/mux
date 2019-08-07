package main

import (
	"bufio"
	"errors"
	"log"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
)

type testCommunicator struct {
	test  *testing.T
	read  string
	write string
}

func (c *testCommunicator) Read(buffer []byte) (int, error) {
	var size = 10
	if size > len(c.read) {
		size = len(c.read)
	}
	if size == 0 {
		return 0, errors.New("EOF")
	}

	data := []byte(c.read[:size])
	log.Println("Read [", strings.ReplaceAll(c.read[:size], "\n", "|"), "]")

	c.read = c.read[size:]
	copy(buffer, data)
	return size, nil
}

func (c *testCommunicator) Write(buffer []byte) (int, error) {
	str := string(buffer)
	size := len(str)
	log.Println("Write [", strings.ReplaceAll(str, "\n", "|"), "]")

	assert.LessOrEqual(c.test, size, len(c.write), str)
	assert.Equal(c.test, c.write[:size], str)
	c.write = c.write[size:]
	return len(buffer), nil
}

func lines(s []string) string {
	return strings.Join(s, "\n") + "\n"
}

func TestCommunicate(test *testing.T) {
	c := testCommunicator{
		test: test,
		read: strings.Join([]string{
			"hello",
			"world",
		}, "\n") + "\n",
		write: strings.Join([]string{
			"",
			"Welcome to Echo CLI!",
			"Help:",
			"  Type message and it will be sent back to you.",
			"> hello",
			"> world",
			"> ",
		}, "\n"),
	}

	assert.Equal(test, errors.New("EOF"), Communicate(
		NewEchoCli(), bufio.NewReader(&c), bufio.NewWriter(&c),
	))

	assert.Equal(test, "", c.read)
	assert.Equal(test, "", c.write)
}
