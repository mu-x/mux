import {Component} from './game.js'
import {Point, Size} from './geometry.js'

export const Aligment = {
  CENTER: 'center',
  CORNER: 'corner',
}

export class Rect extends Component {
  constructor(style, size, aligment=Aligment.CENTER) {
    super()
    this.style = style
    this.size = new Size(size)
    this.aligment = aligment
  }
  draw(ctx) {
    let p = this.absPosition
    if (this.aligment == Aligment.CENTER) {
      p = p.add(this.size.center.inverse)
    }
    ctx.fillStyle = this.style
    ctx.fillRect(p.x, p.y, this.size.w, this.size.h)
  }
}

export class Text extends Component {
  constructor(text, color, font, aligment = Aligment.CENTER) {
    super()
    this.color = color
    this.font = font
    this.text = text
    this.aligment = aligment
  }

  draw(ctx) {
    if (this.aligment == Aligment.CENTER) {
      ctx.textBaseline = 'middle'
      ctx.textAlign = 'center'
    } else {
      ctx.textBaseline = ''
      ctx.textAlign = ''
    }

    let p = this.absPosition
    ctx.font = this.font
    ctx.fillStyle = this.color
    ctx.fillText(this.text, p.x, p.y)
  }
}

export class Sprite extends Component {
  constructor(image, size, aligment = Aligment.CENTER) {
    super()
    this.image = image
    this.size = new Size(size || image)
  }
  draw(ctx) {
    let p = this.absPosition
    return ctx.drawImage(this.image, p.x, p.y, this.size.w, this.size.h)
  }
}
