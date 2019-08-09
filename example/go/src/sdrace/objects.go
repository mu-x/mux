package main

import (
	"fmt"
	"math/rand"
	"sdrace/game"
	"sdrace/traits"
	"strings"

	"github.com/golang/glog"
)

type gameSettings struct {
	title       string
	ui          game.Size
	roadSpeed   float64
	playerSpeed game.Vector
	botSpeed    float64
	botSpawn    game.Timer
}

func gameSettingsFromModes(modes string) (gameSettings, error) {
	m := gameSettings{
		title:       "SD Race",
		ui:          game.Size{W: 300, H: 800},
		roadSpeed:   1000,
		playerSpeed: game.Vector{X: 200, Y: 400},
		botSpeed:    500,
		botSpawn:    game.Timer{Timeout: 3, Randimize: 50},
	}

	for _, n := range strings.TrimSpace(modes) {
		switch n {
		case 'e':
			m.title += " *extreem"
			m.botSpawn.Timeout /= 2
			m.botSpawn.Randimize = 70
		case 's':
			m.title += " *slow"
			m.roadSpeed /= 2
			m.botSpeed /= 2
		case 'p':
			m.title += " *predictable"
			m.botSpawn.Randimize = 0
		default:
			return m, fmt.Errorf("Unsupported game mode: %v", n)
		}
	}

	return m, nil
}

func runGame(ui game.UI, m gameSettings) error {
	if err := ui.Init(m.title, m.ui); err != nil {
		return err
	}
	defer ui.Destroy()

	c := game.NewController(ui)
	defer c.Destroy()

	laneW := m.ui.W / 3
	carS := game.Size{W: laneW * 0.7, H: laneW * 1.6}
	laneX := func(n int) float64 { return laneW/2 + laneW*float64(n) }

	c.NewObject(
		"road",
		m.ui.Geometry(),
		[]game.Trait{traits.NewScrollingSprite(c.UI.Sprite("road"), m.roadSpeed)},
	).Prioritized = true //< Keep it behind everything.

	newBorder := func(n string, g game.Geometry) {
		c.NewObject("border_"+n, g, []game.Trait{traits.NewCollide(nil)})
	}

	newBorder("left", game.NewGeometry(-1, m.ui.H/2, 1, m.ui.H))
	newBorder("right", game.NewGeometry(m.ui.W, m.ui.H/2, 1, m.ui.H))
	newBorder("bot", game.NewGeometry(m.ui.W/2, m.ui.H+carS.H, m.ui.W, 1))

	c.NewObject(
		"player",
		game.Geometry{
			Vector: game.Vector{X: laneX(1), Y: m.ui.H - carS.H},
			Size:   carS,
		},
		[]game.Trait{
			traits.NewStaticSprite(c.UI.Sprite("porsche")),
			traits.NewKeyMove(m.playerSpeed, m.ui.Geometry()),
			traits.NewCollide(func(cl traits.Collision) {
				glog.Warningf("The player %v has crashed", cl.Self)
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
				traits.NewAutoMove(game.Vector{X: 0, Y: m.botSpeed}),
				traits.NewCollide(func(cl traits.Collision) {
					if is(cl.Other, "border") || is(cl.Other, "bot_") {
						cl.Self.Destroy()
					}
				}),
			},
		)
	}

	glog.Info("Starting loop...")
	for {
		if _, isT := m.botSpawn.Check(c.TimeDelta()); isT {
			spawnBotCar()
		}

		if err := c.RunFrame(); err != nil {
			glog.Infof("End loop: %v", err)
			return nil
		}
	}
}
