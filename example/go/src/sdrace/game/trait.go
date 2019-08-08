package game

// Trait represents what happen to an Object on specific events.
type Trait interface {
	Owner() *Object
	SetOwner(owner *Object)
	Update(c *Controller)
	Destroy()
}

// BaseTrait is a Trait implementation helper.
type BaseTrait struct {
	owner *Object
}

// Owner returns an owner Object.
func (t *BaseTrait) Owner() *Object {
	if t.owner == nil {
		panic("This trait has no owner")
	}

	return t.owner
}

// SetOwner assignes an owner Object.
func (t *BaseTrait) SetOwner(owner *Object) {
	if owner != nil && t.owner != nil {
		panic("This trais already have an owner")
	}

	t.owner = owner
}

// Destroy should free resurces.
func (t *BaseTrait) Destroy() {
}
