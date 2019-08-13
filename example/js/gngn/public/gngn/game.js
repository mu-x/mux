import {Point, Size} from './geometry.js'

export class Game {
  constructor(canvas, state) {
    this.canvas = canvas
    this.screen = new Size(canvas)
    this.world = new World()
    this.resources = {}
    this.resources_loading = 0
  }

  image(path) {
    return this._resource(Image, path)
  }
  _resource(type, path) {
    let res = this.resources[path]
    if (res) {
      if (res.type != type) {
        throw Error(`File '${path}' is already loaded as '${res.type}'`)
      }
      return res
    }

    res = new type()
    res.type = type
    res.src = path
    res.onload = () => {
      console.log('Loaded', type, 'from', path)
      this.resources_loading -= 1
    }

    console.log('Loading', type, 'from', path, '...')
    this.resources_loading += 1
    this.resources[path] = res
    return res
  }

  run(now) {
    if (this.world.state != State.ENABLED) {
      return console.log("Game Over, world state:", this.world.state)
    }

    let deltaTime = (now && this.lastTime) ? now - this.lastTime : 0;
    this.lastTime = now
    if (!this.resources_loading) {
      this.world.recursiveUpdate(deltaTime)
    }

    let ctx = this.canvas.getContext('2d')
    this.world.recursiveDraw(ctx)
    if (this.resources_loading && this.preloader) {
      this.preloader.update()
    }

    requestAnimationFrame(now => this.run(now))
  }
}

export const State = {
  ENABLED: "active",
  DISABLED: "disabled",
  DEAD: "dead",
}

export class Component {
  constructor(position, ...children) {
    this.parent = null
    this.state = State.ENABLED
    this.position = new Point(position)

    this._children = []
    children.forEach(c => this.addChild(c))
  }

  get absPosition () {
    return new Point(this.position).add((this.parent || {}).absPosition)
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
