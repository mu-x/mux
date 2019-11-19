import { Attribute, Component } from './component.js'
import { Point } from './geometry.js'
import { Controller } from './controls.js'

export class AutoMover extends Attribute {
  constructor(
    owner: Component,
    public speed: Point,
  ) {
    super(owner)
  }

  update(dt: number) {
    this.owner.position = this.owner.position.add(this.speed.scale(dt))
  }
}

export class ControllerMover extends Attribute {
  constructor(
    owner: Component,
    public controller: Controller,
    public speedMap: {},
  ) {
    super(owner)
  }

  update(dt: number) {
    this.controller.keys.forEach((k: any) => {
      let p = new Point(this.speedMap[k] || {})
      this.owner.position = this.owner.position.add(p.scale(dt))
    })
  }
}
