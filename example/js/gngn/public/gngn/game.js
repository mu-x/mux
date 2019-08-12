export default class Game {
  constructor(canvas) {
    this.canvas = canvas
    this.world = new World()
    this.world.position = {x: canvas.width/2, y: canvas.height/2}
  }

  run(now) {
    if (this.world.state != State.ENABLED) {
      return console.log("Game Over, world state:", this.world.state)
    }

    let deltaTime = (now && this.lastTime) ? now - this.lastTime : 0;
    this.lastTime = now

    this.world.recursiveUpdate(deltaTime)
    this.world.recursiveDraw(this.canvas.getContext('2d'))

    requestAnimationFrame(now => this.run(now))
  }
}

export const State = {
  ENABLED: "active",
  DISABLED: "disabled",
  DEAD: "dead",
}

export class Component {
  constructor(...children) {
    this.parent = null
    this.state = State.ENABLED

    this._children = []
    children.forEach(c => this.addChild(c))
  }

  get absPosition () {
    let p = (this.parent || {}).position || {x: 0, y: 0}
    let s = this.position || {x: 0, y: 0}
    return {x: s.x + p.x, y: s.y + p.y}
  }

  addChild(child) {
    console.log('Add component', child, 'to', this)
    child.parent = this
    this._children.push(child)
  }
  addChildren(...children) {
    children.forEach(c => this.addChild(c))
  }

  update(dt) {
    // To be overriden.
  }
  recursiveUpdate(dt) {
    if (this.State == State.ENABLED) {
      this.update(dt)
      this._children.forEach(c => c.recursiveUpdate(dt))
    }
    if (this.State == State.DEAD && this.parent) {
      console.log('Remove dead component', this, 'from', this.parent)
      this.parent._children = this.parent._children.filter(c => c != this)
    }
  }

  draw(ctx) {
    // To be overriden.
  }
  recursiveDraw(ctx) {
    if (this.state == State.ENABLED) {
      this.draw(ctx)
      this._children.forEach(c => c.recursiveDraw(ctx))
    }
  }
}

class World extends Component {
}
