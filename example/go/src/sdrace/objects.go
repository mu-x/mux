package main

import (
	"fmt"
	"log"
	"math/rand"
	"sdrace/game"
	"sdrace/traits"
	"strings"
)

const (
	roadSpeedY   = 1000
	playerSpeedX = 300
	playerSpeedY = 300
	botCarSpeedY = 500
)

type sizes struct {
	ui    game.Size
	laneW float64
	car   game.Size
}

func newSizes(c *game.Controller) (s sizes) {
	s.ui = c.UI.Size()
	s.laneW = s.ui.W / 3
	s.car = game.Size{W: s.laneW * 0.7, H: s.laneW * 1.6}
	return s
}

func (s *sizes) laneX(n int) float64 {
	return s.laneW/2 + s.laneW*float64(n)
}

// ---

func newBackground(c *game.Controller) {
	s := newSizes(c)
	c.NewObject(
		"road", s.ui.Geometry(),
		[]game.Trait{traits.NewStaticSprite(c.UI.Sprite("road"))},
	)

	newBorder := func(n string, g game.Geometry) {
		c.NewObject("border_"+n, g, []game.Trait{traits.NewCollide(nil)})
	}

	newBorder("left", game.NewGeometry(-1, 0, 1, s.ui.H))
	newBorder("right", game.NewGeometry(s.ui.W, -1, 1, s.ui.H))
	newBorder("bot", game.NewGeometry(0, s.ui.H+s.car.H, s.ui.W, 1))
}

func newPlayer(c *game.Controller) {
	s := newSizes(c)
	c.NewObject(
		"player",
		game.Geometry{
			Vector: game.Vector{X: s.laneX(1), Y: s.ui.H - s.car.H},
			Size:   s.car,
		},
		[]game.Trait{
			traits.NewStaticSprite(c.UI.Sprite("porsche")),
			traits.NewKeyMove(game.Vector{X: playerSpeedX, Y: playerSpeedY}, s.ui.Geometry()),
			traits.NewCollide(func(cl traits.Collision) {
				log.Printf("The player %v has crashed", cl.Self)
				c.GameOver = true
			}),
		},
	)
}

func newBotCar(c *game.Controller) {
	s := newSizes(c)
	sprite := fmt.Sprintf("bot_%v", rand.Intn(4))
	c.NewObject(
		sprite,
		game.Geometry{
			Vector: game.Vector{X: s.laneX(rand.Intn(3)), Y: -s.car.H},
			Size:   s.car,
		},
		[]game.Trait{
			traits.NewStaticSprite(c.UI.Sprite(sprite)),
			traits.NewAutoMove(game.Vector{X: 0, Y: botCarSpeedY}),
			traits.NewCollide(func(cl traits.Collision) {
				if strings.HasPrefix(cl.Other.Name, "border") {
					cl.Self.Destroy()
				}
			}),
		},
	)
}
