import {Component} from './game.js'
import {Point, Size, OptSize} from './geometry.js'

export enum Aligment {
  CENTER = 'center',
  CORNER = 'corner',
}

export class Rect extends Component {
  style: string
  size: Size
  aligment: Aligment

  constructor(style: string, size: OptSize, aligment = Aligment.CENTER) {
    super()
    this.style = style
    this.size = new Size(size)
    this.aligment = aligment
  }

  draw(ctx: CanvasRenderingContext2D) {
    let p = this.absPosition
    if (this.aligment == Aligment.CENTER) {
      p = p.add(this.size.center.inverse)
    }
    ctx.fillStyle = this.style
    ctx.fillRect(p.x, p.y, this.size.width, this.size.height)
  }
}

export class Text extends Component {
  text: string
  style: string
  font: string
  aligment: Aligment

  constructor(text: string, style = '', font = '', aligment = Aligment.CENTER) {
    super()
    this.text = text
    this.style = style
    this.font = font
    this.aligment = aligment
  }

  draw(ctx: CanvasRenderingContext2D) {
    if (this.aligment == Aligment.CENTER) {
      ctx.textAlign = 'center'
      ctx.textBaseline = 'middle'
    } else {
      ctx.textAlign = 'left'
      ctx.textBaseline = 'top'
    }

    let p = this.absPosition
    ctx.font = this.font
    ctx.fillStyle = this.style
    ctx.fillText(this.text, p.x, p.y)
  }
}

export class Sprite extends Component {
  image: HTMLImageElement
  size: Size

  constructor(image: HTMLImageElement, size: OptSize = {}, aligment = Aligment.CENTER) {
    super()
    this.image = image
    this.size = new Size(size || image)
  }

  draw(ctx: CanvasRenderingContext2D) {
    let p = this.absPosition
    return ctx.drawImage(this.image, p.x, p.y, this.size.width, this.size.height)
  }
}
