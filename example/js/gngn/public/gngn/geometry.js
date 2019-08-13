export class Point {
  constructor(obj) {
    this.x = obj ? (obj.x || 0) : 0
    this.y = obj ? (obj.y || 0) : 0
  }

  get inverse () {
    return new Point({x: -this.x, y: -this.y})
  }

  add(obj) {
    let p = new Point(obj)
    return new Point({x: this.x + p.x, y: this.y + p.y})
  }
  mul(obj) {
    return new Point(typeof obj == 'number'
      ? {x: this.x * obj, y: this.y * obj}
      : {x: this.x * obj.x, y: this.y * obj.y}
    )
  }
}

export class Size {
  constructor(obj) {
    this.w = obj ? (obj.w || obj.width || 0) : 0
    this.h = obj ? (obj.h || obj.height || 0) : 0
  }

  get center () {
    return new Point({x: this.w/2, y: this.h/2})
  }

  add(obj) {
    let p = new Point(obj)
    return new Size({w: this.w + p.x, h: this.h + p.y})
  }
}
