package main

import (
	"fmt"

	"github.com/veandco/go-sdl2/sdl"
)

const gameName = "SD Race"
const screenWidth = 300
const screenHeight = 800

func main() {
	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		panic(err)
	}

	window, err := sdl.CreateWindow(
		gameName, sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, sdl.WINDOW_OPENGL)
	if err != nil {
		panic(err)
	}
	defer window.Destroy()

	renderer, err := sdl.CreateRenderer(window, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		panic(err)
	}
	defer renderer.Destroy()

	road := newObject(renderer, "road", screenWidth, screenHeight)
	defer road.Destroy()

	carWidth := int32(screenWidth / 4)
	player := newObject(renderer, "porsche", carWidth, carWidth*2)
	defer player.Destroy()

	fmt.Println("Game is loaded, start cycle...")
	for {
		for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
			switch event.(type) {
			case *sdl.QuitEvent:
				return
			}
		}

		renderer.Clear()
		road.Draw()
		player.Draw()
		renderer.Present()
	}
}
