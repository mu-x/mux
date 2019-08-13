import {Point, Size} from './geometry.js'

export class Game {
  canvas: HTMLCanvasElement
  screen: Size
  world: World
  preloader?: Component

  private _resources: {}
  private _resources_loading: number
  private _lastFrameTime: number = 0

  constructor(canvas) {
    this.canvas = canvas
    this.screen = new Size(canvas)
    this.world = new World()
    this._resources = {}
    this._resources_loading = 0
  }

  image(path: string) {
    return this._resource(Image, path)
  }
  _resource(type: any, path: string) {
    let res = this._resources[path]
    if (res) {
      if (res.type != type)
        throw Error(`File '${path}' is already loaded as '${res.type}'`)

      return res
    }

    res = new type()
    res.type = type
    res.src = path
    res.onload = () => {
      console.log('Loaded', type, 'from', path)
      this._resources_loading -= 1
    }

    console.log('Loading', type, 'from', path, '...')
    this._resources_loading += 1
    this._resources[path] = res
    return res
  }

  run(now: number = 0) {
    if (this.world.state != State.ENABLED)
      return console.log("Game Over, world state:", this.world.state)

    let deltaTime = (now && this._lastFrameTime) ? now - this._lastFrameTime : 0;
    this._lastFrameTime = now
    if (!this._resources_loading)
      this.world.recursiveUpdate(deltaTime)

    let ctx = this.canvas.getContext('2d')
    if (!ctx)
      throw Error("Canvas does not have 2D context")

    this.world.recursiveDraw(ctx)
    if (this._resources_loading && this.preloader) {
      this.preloader.draw(ctx)
    }

    requestAnimationFrame(now => this.run(now))
  }
}

export enum State {
  ENABLED = "active",
  DISABLED = "disabled",
  DEAD = "dead",
}

export class Component {
  state: State
  parent?: Component
  position?: Point

  private _children: Component[]

  constructor(position = {}, ...children: Component[]) {
    this.state = State.ENABLED
    this.position = new Point(position)

    this._children = []
    children.forEach(c => this.addChild(c))
  }

  get absPosition(): Point {
    return new Point(this.position).add(
      this.parent ? this.parent.absPosition : new Point())
  }

  addChild(child: Component) {
    console.log('Add component', child, 'to', this)
    child.parent = this
    this._children.push(child)
  }
  addChildren(...children: Component[]) {
    children.forEach(c => this.addChild(c))
  }

  update(dt: number) {
    // To be overriden.
  }
  recursiveUpdate(dt:number) {
    if (this.state == State.ENABLED) {
      this.update(dt)
      this._children.forEach(c => c.recursiveUpdate(dt))
    }
    if (this.state == State.DEAD && this.parent) {
      console.log('Remove dead component', this, 'from', this.parent)
      this.parent._children = this.parent._children.filter(c => c != this)
    }
  }

  draw(ctx: CanvasRenderingContext2D) {
    // To be overriden.
  }
  recursiveDraw(ctx: CanvasRenderingContext2D) {
    if (this.state == State.ENABLED) {
      this.draw(ctx)
      this._children.forEach(c => c.recursiveDraw(ctx))
    }
  }
}

class World extends Component {
}
