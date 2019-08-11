package neural

import (
	"fmt"
	"math/rand"

	"github.com/golang/glog"
	"gonum.org/v1/gonum/mat"
)

// RandFloat64 normaly distributed in [min, max].
func RandFloat64(min, max float64) float64 {
	return min + rand.Float64()*(max-min)
}

// Sigmoid is just fast to calculate.
func Sigmoid(v float64) float64 {
	if v < 0 {
		return 0
	}
	if v < 1 {
		return v
	}
	return 1
}

// Layer of the network.
type Layer struct {
	Weights *mat.Dense
}

func (lr *Layer) String() string {
	return fmt.Sprintf("Lr%v", lr.Grid())
}

// Grid representation of Weights.
func (lr *Layer) Grid() (m [][]float64) {
	rows, cols := lr.Weights.Caps()
	for c := 0; c < cols; c++ {
		v := []float64{}
		for r := 0; r < rows; r++ {
			v = append(v, lr.Weights.At(r, c))
		}
		m = append(m, v)
	}
	return m
}

// Apply layer to ins to get outs.
func (lr *Layer) Apply(ins, outs []float64) {
	r, c := lr.Weights.Caps()
	i := mat.NewDense(1, r, ins)
	o := mat.NewDense(1, c, outs)
	o.Mul(i, lr.Weights)
	o.Apply(func(_, _ int, v float64) float64 { return Sigmoid(v) }, o)
	if glog.V(3) {
		glog.Infof("%v : %v -> %v", lr.String(), ins, outs)
	}
}
