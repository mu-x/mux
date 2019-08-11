# SD Race

The SDL based Racing Game.

## Build & Run

Developed and tested on Ubuntu 16.
```
    apt install libsdl2{,-image,-mixer,-ttf,-gfx}-dev

    go get \
        github.com/veandco/go-sdl2/... \
        github.com/gonum/gonum/... \
        github.com/golang/glog

    go test ./...

    go build
    ./sdrace
```
