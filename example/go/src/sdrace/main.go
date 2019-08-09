package main

import (
	"fmt"
	"sdrace/game"
)

func main() {
	fmt.Println("Starting game...")
	if err := runGame(game.NewSdlUI()); err != nil {
		fmt.Println("Error: " + err.Error())
	} else {
		fmt.Println("Game Over, You Died!")
	}
}
