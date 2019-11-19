import { Point, Size } from './geometry.js'

export class Attribute {
  constructor(public owner: Component) {
    owner.attributes.push(this)
  }

  update(dt: number) {}
  draw(ctx: CanvasRenderingContext2D) {}
}

export class Component {
  name: string
  parent?: Component
  position: Point

  isAlive: boolean = true
  attributes: Attribute[] = []
  children: Component[] = []

  constructor(name: string, parent?: Component, position = {}) {
    this.name = name
    this.parent = parent
    this.position = new Point(position)
    if (parent)
      parent.children.push(this)
  }

  get absPosition(): Point {
    return new Point(this.position).add(
      this.parent ? this.parent.absPosition : new Point())
  }

  update(dt:number) {
    this.attributes.forEach(b => b.update(dt))
    this.children = this.children.filter(c => c.isAlive)
    this.children.forEach(c => c.update(dt))
  }

  draw(ctx: CanvasRenderingContext2D) {
    this.attributes.forEach(b => b.draw(ctx))
    this.children.forEach(c => c.draw(ctx))
  }
}
