package mycli

import "sync"

// Cli represents a generic CLI inteface.
type Cli interface {
	Name() string
	Help() []string
	Send(m string) *string
}

// NewSyncCli creates syncronized wrapper over Cli.
func NewSyncCli(c Cli) Cli {
	return &syncCli{cli: c}
}

type syncCli struct {
	cli   Cli
	mutex sync.Mutex
}

func (s *syncCli) Name() string {
	s.mutex.Lock()
	defer s.mutex.Unlock()
	return s.cli.Name()
}

func (s *syncCli) Help() []string {
	s.mutex.Lock()
	defer s.mutex.Unlock()
	return s.cli.Help()
}

func (s *syncCli) Send(m string) *string {
	s.mutex.Lock()
	defer s.mutex.Unlock()
	return s.cli.Send(m)
}
