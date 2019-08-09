package traits

import (
	"sdrace/game"
)

type sprite struct {
	game.BaseTrait
	sprite         game.Sprite
	scrollSpeed    float64
	scrollPosition float64
}

// NewStaticSprite makes a trait to draw static sprite.
func NewStaticSprite(s game.Sprite) game.Trait {
	return &sprite{sprite: s}
}

// NewScrollingSprite makes a trait to draw scrolling sprite sprite.
func NewScrollingSprite(s game.Sprite, ss float64) game.Trait {
	return &sprite{sprite: s, scrollSpeed: ss}
}

func (st *sprite) Update(c *game.Controller) {
	st.scrollPosition += st.scrollSpeed * c.TimeDelta()
	for st.scrollPosition >= c.UI.Size().H {
		st.scrollPosition -= c.UI.Size().H
	}

	if st.scrollPosition == 0 {
		c.UI.Draw(st.sprite, st.Owner().Geometry)
		return
	}

	g := st.Owner().Geometry
	g.Y += st.scrollPosition
	c.UI.Draw(st.sprite, g)

	g.Y -= g.H
	c.UI.Draw(st.sprite, g)
}
