package traits

import (
	"sdrace/game"

	"github.com/veandco/go-sdl2/sdl"
)

type moveMode = int

const (
	autoMove moveMode = iota
	keyMove
)

type move struct {
	game.BaseTrait
	speed game.Vector
	mode  moveMode
}

// NewAutoMove moves object according to speed.
func NewAutoMove(speed game.Vector) game.Trait {
	return &move{speed: speed, mode: autoMove}
}

// NewKeyMove moves object according to user input with max speed.
func NewKeyMove(speed game.Vector) game.Trait {
	return &move{speed: speed, mode: keyMove}
}

func (m *move) Update(c *game.Controller) {
	dist := m.speed.MulScalar(c.TimeDelta())
	if m.mode == keyMove {
		dist = dist.MulEach(calcKeyMove(c.UI.Input()))
	}

	v := &m.Owner().Vector
	*v = v.Add(dist)
}

func calcKeyMove(k game.Keys) game.Vector {
	v := game.Vector{}

	if k[sdl.SCANCODE_LEFT] == 1 {
		v.X = -1
	} else if k[sdl.SCANCODE_RIGHT] == 1 {
		v.X = +1
	}

	if k[sdl.SCANCODE_UP] == 1 {
		v.Y = -1
	} else if k[sdl.SCANCODE_DOWN] == 1 {
		v.Y = +1
	}

	return v
}
