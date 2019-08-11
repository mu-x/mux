package neural

import (
	"encoding/json"
	"fmt"

	"github.com/golang/glog"

	"gonum.org/v1/gonum/mat"
)

// Network - a neural network.
type Network struct {
	Layers  []Layer
	tmpOuts [][]float64
}

func (net *Network) String() string {
	return fmt.Sprintf("Net%v", net.describe().Sizes)
}

// NewRandomNetwork with layers by sizes and random weights.
func NewRandomNetwork(sizes []int) Network {
	return NewNetwork(sizes, nil)
}

// NewNetworkJSON from JSON representation.
func NewNetworkJSON(d []byte) (Network, error) {
	nd := netDescription{}
	if err := json.Unmarshal(d, &nd); err != nil {
		return Network{}, err
	}
	return NewNetwork(nd.Sizes, nd.Weights), nil
}

// NewNetwork with layers by sizes and specific weights.
func NewNetwork(sizes []int, weights [][]float64) (net Network) {
	ins, sizes := sizes[0], sizes[1:]
	for i, outs := range sizes {
		w := []float64{}
		if weights != nil {
			w = weights[i]
		} else {
			w = make([]float64, ins*outs)
			for i := range w {
				w[i] = RandFloat64(-1, 1)
			}
		}

		lr := Layer{Weights: mat.NewDense(ins, outs, w)}
		if glog.V(2) {
			glog.Info(lr.String())
		}

		net.Layers = append(net.Layers, lr)
		ins = outs //< For the next layer.
	}
	return net
}

// Sizes of all layers (ins, hidden layers and outs).
func (net *Network) Sizes() []int {
	return net.describe().Sizes
}

// Apply network to ins to get outs in return.
func (net *Network) Apply(ins []float64) []float64 {
	for i, lr := range net.Layers {
		if i == len(net.tmpOuts) {
			_, s := lr.Weights.Caps()
			net.tmpOuts = append(net.tmpOuts, make([]float64, s))
		}

		lr.Apply(ins, net.tmpOuts[i])
		ins = net.tmpOuts[i] //< Prepare to next layer.
	}

	return ins //< Last preparation was not needed.
}

// ToJSON for later use (e.g. NewNetworkJson).
func (net *Network) ToJSON() []byte {
	d, err := json.Marshal(net.describe())
	if err != nil {
		panic(fmt.Errorf("Unexpected serialization error: %v", err))
	}
	return d
}

type netDescription struct {
	Sizes   []int
	Weights [][]float64
}

func (net *Network) describe() (s netDescription) {
	if len(net.Layers) != 0 {
		d, _ := net.Layers[0].Weights.Caps()
		s.Sizes = append(s.Sizes, d)

		for _, lr := range net.Layers {
			_, d := lr.Weights.Caps()
			s.Sizes = append(s.Sizes, d)
			s.Weights = append(s.Weights, lr.Weights.RawMatrix().Data)
		}
	}

	return s
}
