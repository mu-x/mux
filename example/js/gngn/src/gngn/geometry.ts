export interface OptPoint {
  x?: number
  y?: number
}

export class Point {
  x: number
  y: number

  constructor(v: OptPoint = {}) {
    this.x = v.x || 0
    this.y = v.y || 0
  }

  get inverse () {
    return new Point({x: -this.x, y: -this.y})
  }

  add(v: OptPoint) {
    let p = new Point(v)
    return new Point({x: this.x + p.x, y: this.y + p.y})
  }
  scale(v: number | OptPoint) {
    if (typeof v === 'number')
      return new Point({x: this.x * v, y: this.y * v})

    let obj: any = v //< Workaround for TS2532.
    return new Point({x: this.x * obj.x || 1, y: this.y * obj.y || 1})
  }
}

export interface OptSize {
  width?: number
  height?: number
}

export class Size {
  width: number
  height: number

  constructor(v: OptSize = {}) {
    this.width = v.width || 0
    this.height = v.height || 0
  }

  get center () {
    return new Point({x: this.width / 2, y: this.height / 2})
  }

  add(v: {x?: number, y?: number} = {}) {
    let p = new Point(v)
    return new Size({width: this.width + p.x, height: this.height + p.y})
  }
}
