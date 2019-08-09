package main

import (
	"flag"
	"fmt"
	"math/rand"
	"os"
	"sdrace/game"
	"time"
)

var modes = flag.String("m", "", "list of game modes, supported: sp")

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	os.Args = append(os.Args, "-logtostderr")
	flag.Parse()

	s, err := gameSettingsFromModes(*modes)
	if err != nil {
		fmt.Println("Error: " + err.Error())
		return
	}

	fmt.Println("Starting game: " + s.title)
	if err := runGame(game.NewSdlUI(), s); err != nil {
		fmt.Println("Error: " + err.Error())
	} else {
		fmt.Println("Game Over, You Died!")
	}
}
