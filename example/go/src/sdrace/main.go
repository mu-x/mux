package main

import (
	"fmt"
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

	timeSinceBot := 100.0
	fmt.Println("##### Start game loop...")
	for {
		timeSinceBot += controller.TimeDelta()
		if timeSinceBot > 1.5 {
			newBotCar(controller)
			timeSinceBot = 0
		}

		if err := controller.RunFrame(); err != nil {
			fmt.Println("##### End game loop:", err)
			return
		}
	}
}
