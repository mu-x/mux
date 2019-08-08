package traits

import (
	"sdrace/game"
)

type sprite struct {
	game.BaseTrait
	sprite game.Sprite
}

// NewStaticSprite makes a trait to draw static sprite.
func NewStaticSprite(s game.Sprite) game.Trait {
	return &sprite{sprite: s}
}

func (st *sprite) Update(c *game.Controller) {
	c.UI.Draw(st.sprite, st.Owner().Rect())
}
