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
	gameName            = "SD Race"
	gameW               = 300
	gameH               = 800
	roadSpeedY          = 450
	playerSpeedX        = 300
	playerSpeedY        = 300
	botCarSpeedY        = 500
	botCarSpawnInterval = 3
	botCarSpawnRandom   = 50
)

func runGame(ui game.UI) error {
	if err := ui.Init(gameName, gameW, gameH); err != nil {
		return err
	}
	defer ui.Destroy()

	c := game.NewController(ui)
	defer c.Destroy()

	uiS := c.UI.Size()
	laneW := uiS.W / 3
	carS := game.Size{W: laneW * 0.7, H: laneW * 1.6}
	laneX := func(n int) float64 { return laneW/2 + laneW*float64(n) }

	c.NewObject(
		"road",
		uiS.Geometry(),
		[]game.Trait{traits.NewScrollingSprite(c.UI.Sprite("road"), roadSpeedY)},
	).Prioritized = true //< Keep it behind everything.

	newBorder := func(n string, g game.Geometry) {
		c.NewObject("border_"+n, g, []game.Trait{traits.NewCollide(nil)})
	}

	newBorder("left", game.NewGeometry(-1, uiS.H/2, 1, uiS.H))
	newBorder("right", game.NewGeometry(uiS.W, uiS.H/2, 1, uiS.H))
	newBorder("bot", game.NewGeometry(uiS.W/2, uiS.H+carS.H, uiS.W, 1))

	c.NewObject(
		"player",
		game.Geometry{
			Vector: game.Vector{X: laneX(1), Y: uiS.H - carS.H},
			Size:   carS,
		},
		[]game.Trait{
			traits.NewStaticSprite(c.UI.Sprite("porsche")),
			traits.NewKeyMove(game.Vector{X: playerSpeedX, Y: playerSpeedY}, uiS.Geometry()),
			traits.NewCollide(func(cl traits.Collision) {
				log.Printf("The player %v has crashed", cl.Self)
				c.GameOver = true
			}),
		},
	)

	is := func(o *game.Object, p string) bool { return strings.HasPrefix(o.Name, p) }
	spawnBotCar := func() {
		sprite := fmt.Sprintf("bot_%v", rand.Intn(4))
		c.NewObject(
			sprite,
			game.Geometry{
				Vector: game.Vector{X: laneX(rand.Intn(3)), Y: -carS.H},
				Size:   carS,
			},
			[]game.Trait{
				traits.NewStaticSprite(c.UI.Sprite(sprite)),
				traits.NewAutoMove(game.Vector{X: 0, Y: botCarSpeedY}),
				traits.NewCollide(func(cl traits.Collision) {
					if is(cl.Other, "border") || is(cl.Other, "bot_") {
						cl.Self.Destroy()
					}
				}),
			},
		)
	}

	botSpawnTimer := game.Timer{Timeout: botCarSpawnInterval, Randimize: botCarSpawnRandom}
	log.Printf("Start loop...")
	for {
		if _, isT := botSpawnTimer.Check(c.TimeDelta()); isT {
			spawnBotCar()
		}

		if err := c.RunFrame(); err != nil {
			log.Printf("End loop: %v", err)
			return nil
		}
	}
}
