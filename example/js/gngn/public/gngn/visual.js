import {Component} from './game.js'

export class Rect extends Component {
  constructor(color, w, h) {
    super()
    this.color = color
    this.w = w
    this.h = h
  }
  draw(ctx) {
    let p = this.absPosition
    ctx.fillStyle = this.color
    ctx.fillRect(p.x - this.w/2, p.y - this.h/2, this.w, this.h)
  }
}

export class Text extends Component {
  constructor(color, font, text) {
    super()
    this.color = color
    this.font = font
    this.text = text
  }
  draw(ctx) {
    let p = this.absPosition
    ctx.textBaseline = 'middle';
    ctx.textAlign = 'center';
    ctx.font = this.font
    ctx.fillStyle = this.color
    ctx.fillText(this.text, p.x, p.y)
  }
}
