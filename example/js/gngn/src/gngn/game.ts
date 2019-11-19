import { Point, Size } from './geometry.js'
import { Component } from './component.js'

export default class Game {
  canvas: HTMLCanvasElement
  world = new Component("world")
  preloader?: Component
  speed = 1

  private _resources = {}
  private _resources_loading = 0
  private _lastFrameTime = 0

  constructor(canvas) {
    this.canvas = canvas
  }

  image(path: string): HTMLImageElement {
    return this._resource(Image, path)
  }
  _resource(type: any, path: string): any {
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
    if (!this.world.isAlive)
      return console.log("Game Over!")

    let deltaTime = (now && this._lastFrameTime) ? now - this._lastFrameTime : 0;
    this._lastFrameTime = now
    if (!this._resources_loading)
      this.world.update(deltaTime * this.speed / 1000)

    let ctx = this.canvas.getContext('2d')
    if (!ctx)
      throw Error("Canvas does not have 2D context")

    this.world.draw(ctx)
    if (this._resources_loading && this.preloader) {
      this.preloader.draw(ctx)
    }

    requestAnimationFrame(now => this.run(now))
  }
}
