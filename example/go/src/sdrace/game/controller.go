package game

import (
	"errors"
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

type Keys = []uint8
type Sprite = interface{}

// UI communicator.
type UI interface {
	Destroy()
	Size() Size
	Input() Keys

	Sprite(name string) Sprite
	Draw(s Sprite, r sdl.Rect)
	Present()
}

// Controller controlls the game state.
type Controller struct {
	UI       UI
	Speed    float64
	GameOver bool

	lastCycle    *time.Time
	currentCycle *time.Time
	objects      objectPool
}

// NewController creates a controller.
func NewController(ui UI) *Controller {
	return &Controller{
		UI:       ui,
		Speed:    1,
		GameOver: false,
		objects:  objectPool{map[*Object]bool{}},
	}
}

// Destroy removes all object's traits and removes it from the ObjectPool.
func (c *Controller) Destroy() {
	c.UI.Destroy()
	c.objects.Destroy()
}

// TimeDelta returns how mutch time has passed since last frame (in seconds).
func (c *Controller) TimeDelta() float64 {
	if c.lastCycle == nil || c.currentCycle == nil {
		return 0
	}

	td := c.currentCycle.Sub(*c.lastCycle)
	return td.Seconds() * c.Speed
}

// NewObject creates a new game object.
func (c *Controller) NewObject(name string, g Geometry, ts []Trait) *Object {
	return NewObject(&c.objects, name, g, ts)
}

// Objects returns all active objects.
func (c *Controller) Objects() (obs []*Object) {
	for obj := range c.objects.objects {
		if obj.Active {
			obs = append(obs, obj)
		}
	}

	return obs
}

// RunFrame updates the game state.
func (c *Controller) RunFrame() error {
	if c.GameOver {
		return errors.New("Game Over")
	}

	for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
		if event.GetType() == sdl.QUIT {
			return errors.New("Quit")
		}
	}

	now := time.Now()
	c.lastCycle = c.currentCycle
	c.currentCycle = &now

	c.updateObjects()
	c.UI.Present()
	return nil
}

func (c *Controller) updateObjects() {
	for _, obj := range c.Objects() {
		obj.EachTrait(func(t Trait) {
			// Traits may diactivate it's owner.
			if obj.Active {
				t.Update(c)
			}
		})
	}
}
