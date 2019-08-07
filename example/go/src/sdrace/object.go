package main

import (
	"fmt"

	"github.com/veandco/go-sdl2/img"
	"github.com/veandco/go-sdl2/sdl"
)

type object struct {
	renderer *sdl.Renderer
	texture  *sdl.Texture
	geomerty sdl.Rect
}

func newObject(r *sdl.Renderer, image string, w int32, h int32) object {
	path := "images/" + image + ".png"
	img, err := img.Load(path)
	if err != nil {
		panic(fmt.Errorf("Unable to load image: %v", err))
	}
	defer img.Free()

	tex, err := r.CreateTextureFromSurface(img)
	if err != nil {
		panic(fmt.Errorf("Unable to make texture: %v: %v", path, err))
	}

	return object{r, tex, sdl.Rect{X: 0, Y: 0, W: w, H: h}}
}

func (o *object) Destroy() {
	o.texture.Destroy()
}

func (o *object) Draw() {
	o.renderer.Copy(o.texture, nil, &o.geomerty)
}
