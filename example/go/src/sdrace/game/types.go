package game

import "github.com/veandco/go-sdl2/sdl"

// Vector describes a singe point position.
type Vector struct {
	X, Y float64
}

// NewVector from SDL ints.
func NewVector(x, y int32) Vector {
	return Vector{float64(x), float64(y)}
}

// Add return sum by each component.
func (v Vector) Add(m Vector) Vector {
	return Vector{v.X + m.X, v.Y + m.Y}
}

// MulEach return multiplication by each component.
func (v Vector) MulEach(m Vector) Vector {
	return Vector{v.X * m.X, v.Y * m.Y}
}

// MulScalar returns multiplication by scalar.
func (v Vector) MulScalar(s float64) Vector {
	return Vector{v.X * s, v.Y * s}
}

// Size describes and object size.
type Size struct {
	W, H float64
}

// NewSize from SDL ints.
func NewSize(w, h int32) Size {
	return Size{float64(w), float64(h)}
}

// Center of a Size.
func (s *Size) Center() Vector {
	return Vector{X: s.W / 2, Y: s.H / 2}
}

// Geometry represents an object's basic geometry.
type Geometry struct {
	Vector
	Size
}

// NewGeometry construct helper.
func NewGeometry(x, y, w, h float64) Geometry {
	return Geometry{Vector{x, y}, Size{w, h}}
}

// Rect contsructs SDL int rect.
func (g *Geometry) Rect() sdl.Rect {
	return sdl.Rect{
		X: int32(g.X - g.W/2),
		Y: int32(g.Y - g.H/2),
		W: int32(g.W),
		H: int32(g.H),
	}
}
