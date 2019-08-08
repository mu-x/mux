package main

import (
	"log"
	"sdrace/game"
)

func main() {
	ui, err := game.NewSdlUI("SD Race", game.Size{300, 800})
	if err != nil {
		log.Printf("Unable to init UI: %v", err)
		return
	}
	defer ui.Destroy()

	controller := game.NewController(ui)
	defer controller.Destroy()

	newBackground(controller)
	newPlayer(controller)

	log.Println("Game is loaded, start cycle...")
	for {
		if err := controller.RunFrame(); err != nil {
			log.Println("Game over:", err)
			return
		}
	}
}
