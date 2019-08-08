package game

import (
	"fmt"
	"reflect"
)

// ObjectPool keeps track of all created objects.
type objectPool struct {
	objects map[*Object]bool
}

// Destroy destroys all objects in the pool.
func (pool *objectPool) Destroy() {
	for obj := range pool.objects {
		obj.pool = nil //< Avoid destruction loop.
		obj.Destroy()
	}
}

// Object is a separate entity in a game represented by a set of Traits.
type Object struct {
	Geometry
	Name   string
	Active bool

	pool   *objectPool
	traits map[reflect.Type]Trait
}

// NewObject creates new object registred in the ObjectPool.
func NewObject(pool *objectPool, name string, g Geometry, ts []Trait) *Object {
	obj := &Object{
		Geometry: g, Name: name, Active: true,
		pool: pool, traits: map[reflect.Type]Trait{},
	}

	for _, t := range ts {
		obj.addTrait(t)
	}

	pool.objects[obj] = true
	return obj
}

// Destroy removes all object's traits and removes it from the ObjectPool.
func (obj *Object) Destroy() {
	obj.EachTrait(func(t Trait) {
		t.SetOwner(nil)
		t.Destroy()
	})

	if obj.pool != nil {
		delete(obj.pool.objects, obj)
	}
}

// EachTrait applies a function to each trait.
func (obj *Object) EachTrait(function func(t Trait)) {
	for _, t := range obj.traits {
		function(t)
	}
}

func (obj *Object) addTrait(trait Trait) {
	t := reflect.TypeOf(trait)
	if _, ok := obj.traits[t]; ok {
		panic(fmt.Errorf("Object(%v) trait duplicate: %v", obj.Name, t))
	}

	obj.traits[t] = trait
	trait.SetOwner(obj)
}
