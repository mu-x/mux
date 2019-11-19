export class Controller {
  keys = new Set()

  constructor() {
    document.onkeydown = e => {
      console.debug("Down:", e.key)
      this.keys.add(e.key)
    }
    document.onkeyup = e => {
      console.debug("Up:", e.key)
      this.keys.delete(e.key)
    }
  }
}
