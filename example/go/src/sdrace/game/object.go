package game

import (
	"fmt"
	"log"
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
	Name        string
	Active      bool
	Prioritized bool

	pool   *objectPool
	traits map[reflect.Type]Trait
}

// newObject creates new object registred in the ObjectPool.
func newObject(pool *objectPool, name string, g Geometry, ts []Trait) *Object {
	obj := &Object{
		Geometry: g, Name: name, Active: true,
		pool: pool, traits: map[reflect.Type]Trait{},
	}

	for _, t := range ts {
		obj.addTrait(t)
	}

	pool.objects[obj] = true
	log.Printf("New %v - %v in Pool(%v)", obj, obj.Geometry, len(pool.objects))
	return obj
}

// Destroy removes all object's traits and removes it from the ObjectPool.
func (obj *Object) Destroy() {
	obj.Active = false
	for _, t := range obj.traits {
		t.SetOwner(nil)
		t.Destroy()
	}

	if obj.pool != nil {
		delete(obj.pool.objects, obj)
		log.Printf("Destroyed %v - %v in Pool(%v)", obj, obj.Geometry, len(obj.pool.objects))
	} else {
		log.Printf("Destroyed %v - %v", obj, obj.Geometry)
	}
}

func (obj *Object) String() string {
	return fmt.Sprintf("Obj(%v %p)", obj.Name, obj)
}

// Update updates object's state.
func (obj *Object) Update(c *Controller) {
	for _, t := range obj.traits {
		// Traits are allowed to change object's activity.
		if obj.Active {
			t.Update(c)
		}
	}
}

// EachTrait applies a function to each trait.
func (obj *Object) EachTrait(function func(t Trait)) {
	for _, t := range obj.traits {
		function(t)
	}
}

// SameTrait returns a trait with the same actual type as tr.
func (obj *Object) SameTrait(tr Trait) Trait {
	if ownTr, ok := obj.traits[reflect.TypeOf(tr)]; ok {
		return ownTr
	}

	return nil
}

func (obj *Object) addTrait(trait Trait) {
	t := reflect.TypeOf(trait)
	if _, ok := obj.traits[t]; ok {
		panic(fmt.Errorf("Object(%v) trait duplicate: %v", obj.Name, t))
	}

	obj.traits[t] = trait
	trait.SetOwner(obj)
}
