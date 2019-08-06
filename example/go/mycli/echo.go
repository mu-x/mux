package main

// NewEchoCli creates echo CLI.
func NewEchoCli() Cli {
	return &echoCli{}
}

type echoCli struct {
}

func (c *echoCli) Name() string {
	return "Echo"
}

func (c *echoCli) Help() []string {
	return []string{"Type message and it will be sent back to you."}
}

func (c *echoCli) Send(m string) *string {
	return &m
}
