package main

import (
	"sdrace/game"
	"sdrace/neural"
	"strings"

	"github.com/veandco/go-sdl2/sdl"
)

var networkSizes = []int{4, 3, 2}

const strearOverweight = 0.2

// neuralUI is a neural network adapter and actual UI (if any).
type neuralUI struct {
	Network neural.Network
	EndUI   game.UI

	size game.Size
	ins  []float64
}

func (ui *neuralUI) Init(name string, s game.Size) error {
	ui.size = s
	ui.ins = make([]float64, ui.Network.Sizes()[0])
	if ui.EndUI != nil {
		return ui.EndUI.Init(name, s)
	}
	return nil
}

func (ui *neuralUI) Destroy() {
	if ui.EndUI != nil {
		ui.EndUI.Destroy()
	}
}

func (ui *neuralUI) Size() game.Size {
	return ui.size
}

func (ui *neuralUI) Input() game.Keys {
	k := make(game.Keys, 256)
	outs := ui.Network.Apply(ui.ins)
	stear := outs[1] - outs[0]
	if stear > strearOverweight {
		k[sdl.SCANCODE_RIGHT] = 1
	} else if stear < -strearOverweight {
		k[sdl.SCANCODE_LEFT] = 1
	}
	return k
}

type sprite struct {
	id       string
	uiSprite interface{}
}

func (ui *neuralUI) Sprite(name string) game.Sprite {
	id := strings.Split(name, "_")[0]
	if ui.EndUI != nil {
		return sprite{id: id, uiSprite: ui.EndUI.Sprite(name)}
	}
	return sprite{id: id}
}

func (ui *neuralUI) Draw(s game.Sprite, g game.Geometry) {
	ls := s.(sprite)
	laneW := ui.size.W / 3
	switch ls.id {
	case "player":
		ui.ins[0] = (g.Y/ui.size.W)*2 - 1
	case "bot":
		ui.ins[1+int(g.X/laneW)] = (g.Y/ui.size.H)*2 - 1
	}

	if ui.EndUI != nil {
		ui.EndUI.Draw(ls.uiSprite, g)
	}
}

func (ui *neuralUI) Present() {
	if ui.EndUI != nil {
		ui.EndUI.Present()
	}
}
