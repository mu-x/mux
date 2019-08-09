package traits

import (
	"sdrace/game"

	"github.com/golang/glog"
)

// Collision event description.
type Collision struct {
	Self  *game.Object
	Other *game.Object
}

type collide struct {
	game.BaseTrait
	handler func(Collision)
}

// NewCollide calls handler when collision is detected.
func NewCollide(handler func(Collision)) game.Trait {
	return &collide{handler: handler}
}

func (cd *collide) Update(c *game.Controller) {
	if cd.handler == nil {
		return
	}

	obj := cd.Owner()
	for _, othObj := range c.Objects() {
		if obj == othObj || !othObj.Active || othObj.SameTrait(cd) == nil {
			continue
		}

		rect := obj.Rect()
		othRect := othObj.Rect()
		if _, does := rect.Intersect(&othRect); does {
			glog.V(1).Infof("Collision detected: %v - %v", obj, othObj)
			cd.handler(Collision{obj, othObj})
		}
	}
}
