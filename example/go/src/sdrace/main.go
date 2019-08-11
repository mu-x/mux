package main

import (
	"flag"
	"fmt"
	"math/rand"
	"os"
	"sdrace/game"
	"sdrace/neural"
	"time"
)

var modes = flag.String("m", "", "list of game modes, supported: sp")
var ai = flag.Bool("ai", false, "AI")

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	os.Args = append(os.Args, "-logtostderr")
	flag.Parse()

	s, err := gameSettingsFromModes(*modes)
	if err != nil {
		fmt.Println("Error: " + err.Error())
		return
	}

	ui := game.NewSdlUI()
	if *ai {
		net := neural.NewRandomNetwork(networkSizes)
		ui = &neuralUI{Network: net, EndUI: ui}
	}

	fmt.Println("Starting game: " + s.title)
	if err := runGame(ui, s); err != nil {
		fmt.Println("Error: " + err.Error())
	} else {
		fmt.Println("Game Over, You Died!")
	}
}
