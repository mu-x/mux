import { Attribute, Component } from './component.js'
import { Size } from './geometry.js'

export enum Aligment {
  CENTER = 'center',
  CORNER = 'corner',
}

export class Rect extends Attribute {
  constructor(
    owner: Component,
    public style: string,
    public size: Size,
    public aligment: Aligment = Aligment.CENTER
  ) {
    super(owner)
  }

  draw(ctx: CanvasRenderingContext2D) {
    let p = this.owner.absPosition
    if (this.aligment == Aligment.CENTER)
      p = p.add(this.size.center.inverse)

    ctx.fillStyle = this.style
    ctx.fillRect(p.x, p.y, this.size.width, this.size.height)
  }
}

export class Text extends Attribute {
  constructor(
    owner: Component,
    public text: string,
    public style = '',
    public font = '',
    public aligment: Aligment = Aligment.CENTER
  ) {
    super(owner)
  }

  draw(ctx: CanvasRenderingContext2D) {
    if (this.aligment == Aligment.CENTER) {
      ctx.textAlign = 'center'
      ctx.textBaseline = 'middle'
    } else {
      ctx.textAlign = 'left'
      ctx.textBaseline = 'top'
    }

    let p = this.owner.absPosition
    ctx.font = this.font
    ctx.fillStyle = this.style
    ctx.fillText(this.text, p.x, p.y)
  }
}

export class Sprite extends Attribute {
  constructor(
    owner: Component,
    public image: HTMLImageElement,
    public aligment: Aligment = Aligment.CENTER,
    public size = new Size(image)
  ) {
    super(owner)
  }

  draw(ctx: CanvasRenderingContext2D) {
    let p = this.owner.absPosition
    ctx.drawImage(this.image, p.x, p.y, this.size.width, this.size.height)
  }
}
