package main

import (
	"sdrace/game"
	"sdrace/traits"
)

const (
	playerSpeedX = 300
	playerSpeedY = 300
)

func newBackground(c *game.Controller) *game.Object {
	s := c.UI.Size()
	return c.NewObject(
		"road",
		game.Geometry{Vector: s.Center(), Size: s},
		[]game.Trait{
			traits.NewStaticSprite(c.UI.Sprite("road")),
		},
	)
}

func newPlayer(c *game.Controller) *game.Object {
	s := c.UI.Size()
	return c.NewObject(
		"player",
		game.NewGeometry(s.W/2, s.H-s.W/4, s.W/4, s.W/2),
		[]game.Trait{
			traits.NewStaticSprite(c.UI.Sprite("porsche")),
			traits.NewKeyMove(game.Vector{X: playerSpeedX, Y: playerSpeedY}),
		},
	)
}
