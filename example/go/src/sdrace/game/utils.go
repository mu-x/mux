package game

import (
	"math/rand"
)

// Timer count time between frames by time delta.
type Timer struct {
	Timeout             float64
	Randimize           int
	nextTimeout, passed float64
	frames              int
}

// Check retuns number of frames sinse last timeout and true if it is timed out now.
func (t *Timer) Check(delta float64) (frames int, isTimeout bool) {
	if t.nextTimeout == 0 {
		t.nextTimeout = t.Timeout
	}

	t.passed += delta
	t.frames++
	frames = t.frames
	if t.passed >= t.nextTimeout {
		t.passed -= t.nextTimeout
		t.frames = 0
		if t.Randimize > 0 {
			randReduce := float64(rand.Intn(t.Randimize)) / 100
			t.nextTimeout = t.Timeout * (1 - randReduce)
		}
	}

	return frames, t.frames == 0
}
