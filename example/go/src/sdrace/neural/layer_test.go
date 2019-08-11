package neural

import (
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
	"gonum.org/v1/gonum/mat"
)

func TestRandFloat64(t *testing.T) {
	for _, d := range []struct{ min, max float64 }{
		{0, 100},
		{-0.1, 0.1},
	} {
		for i := 0; i < 100; i++ {
			n := RandFloat64(d.min, d.max)
			assert.GreaterOrEqual(t, n, d.min)
			assert.LessOrEqual(t, n, d.max)
		}
	}
}

func TestSigmoid(t *testing.T) {
	assert.Equal(t, 0.0, Sigmoid(-0.5))
	assert.Equal(t, 0.5, Sigmoid(0.5))
	assert.Equal(t, 1.0, Sigmoid(1))
	assert.Equal(t, 1.0, Sigmoid(1.5))
}

func TestLayer(t *testing.T) {
	lr := Layer{Weights: mat.NewDense(3, 2, []float64{0.1, 0.2, 0.3, 0.4, -0.1, -0.2})}
	assert.Equal(t, "Lr[[0.1 0.3 -0.1] [0.2 0.4 -0.2]]", lr.String())

	outs := []float64{0, 0}
	for _, d := range []struct {
		ins, expectedOuts []float64
	}{
		{[]float64{1, 1, 1}, []float64{0.3, 0.4}},
		{[]float64{1, 2, 0}, []float64{0.7, 1}},
		{[]float64{0.5, 0.5, 0.5}, []float64{0.15, 0.2}},
	} {
		lr.Apply(d.ins, outs)
		for i := range outs {
			outs[i] = math.Round(outs[i]*1000) / 1000
		}

		assert.Equal(t, d.expectedOuts, outs)
	}
}
