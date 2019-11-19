import { Attribute, Component } from "./component.js";

export class Timer extends Attribute {
  constructor(
    owner: Component,
    public timeout: number,
    public action: (Component) => void,
  ) {
    super(owner)
  }

  private passed: number = 0

  update(dt: number) {
    this.passed += dt
    if (this.passed > this.timeout) {
      this.passed -= this.timeout
      this.action(this.owner)
    }
  }
}
