package game

import (
	"fmt"

	"github.com/golang/glog"
	"github.com/veandco/go-sdl2/img"
	"github.com/veandco/go-sdl2/sdl"
)

type sdlUI struct {
	window   *sdl.Window
	renderer *sdl.Renderer
	sprites  map[string]*sdl.Texture
}

// NewSdlUI creates ne UI.
func NewSdlUI() UI {
	return &sdlUI{sprites: map[string]*sdl.Texture{}}
}

func (u *sdlUI) Init(name string, s Size) error {
	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		return fmt.Errorf("Failed to init SDL: %v", err)
	}

	w, err := sdl.CreateWindow(
		name, sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		int32(s.W), int32(s.H), sdl.WINDOW_OPENGL)
	if err != nil {
		return fmt.Errorf("Failed to create windows: %v", err)
	}

	r, err := sdl.CreateRenderer(w, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		w.Destroy()
		return fmt.Errorf("Failed to create renderer: %v", err)
	}

	u.window = w
	u.renderer = r
	u.sprites = map[string]*sdl.Texture{}
	return nil
}

func (u *sdlUI) Destroy() {
	for _, tx := range u.sprites {
		tx.Destroy()
	}

	u.renderer.Destroy()
	u.window.Destroy()
}

func (u *sdlUI) Size() Size {
	x, y := u.window.GetSize()
	return NewSize(x, y)
}

func (u *sdlUI) Input() []uint8 {
	return sdl.GetKeyboardState()
}

func (u *sdlUI) Sprite(name string) Sprite {
	if t, ok := u.sprites[name]; ok {
		return t
	}

	path := "sprites/" + name + ".png"
	img, err := img.Load(path)
	if err != nil {
		panic(err)
	}
	defer img.Free()

	tx, err := u.renderer.CreateTextureFromSurface(img)
	if err != nil {
		panic(err)
	}

	u.sprites[name] = tx
	glog.V(0).Infof("Sprite %v is loaded", path)
	return tx
}

func (u *sdlUI) Draw(s Sprite, g Geometry) {
	tx := s.(*sdl.Texture)
	if tx == nil {
		panic("Unsupported texture provided")
	}

	r := g.Rect()
	u.renderer.Copy(tx, nil, &r)
}

func (u *sdlUI) Present() {
	u.renderer.Present()
}
