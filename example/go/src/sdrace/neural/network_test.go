package neural

import (
	"math"
	"testing"

	"github.com/stretchr/testify/assert"
)

// See logs: go test -c && ./neural.test -v 3 -logtostderr; rm neural.test
func TestNetwork(t *testing.T) {
	net := NewNetwork([]int{3, 2, 1}, [][]float64{
		{0.1, 0.2, 0.3, 0.4, 0.5, 0.6},
		{0.3, 0.7},
	})
	assert.Equal(t, "Net[3 2 1]", net.String())

	for _, d := range []struct{ ins, expectedOuts []float64 }{
		{[]float64{0.1, 0.5, 0.9}, []float64{0.715}},
		{[]float64{0.9, 0.9, 0.9}, []float64{0.943}},
	} {
		outs := net.Apply(d.ins)
		for i := range outs {
			outs[i] = math.Round(outs[i]*1000) / 1000
		}

		assert.Equal(t, d.expectedOuts, outs)
	}

	json := net.ToJSON()
	expJSON := "{\"Sizes\":[3,2,1],\"Weights\":[[0.1,0.2,0.3,0.4,0.5,0.6],[0.3,0.7]]}"
	assert.Equal(t, expJSON, string(json))

	jNet, err := NewNetworkJSON(json)
	assert.Equal(t, nil, err)
	assert.Equal(t, net.describe(), jNet.describe())
}

func TestRandomNetwork(t *testing.T) {
	net := NewRandomNetwork([]int{5, 3, 2, 1})
	assert.Equal(t, "Net[5 3 2 1]", net.String())

	outs := net.Apply([]float64{0.1, 0.2, 0.3, 0.4, 0.5})
	for _, out := range outs {
		assert.GreaterOrEqual(t, out, 0.0)
		assert.LessOrEqual(t, out, 1.0)
	}
}
