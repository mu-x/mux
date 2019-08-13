export class Counter {
  number: number
  message: string
  constructor(n: number, m: string) {
    this.number = n
    this.message = m
  }
  count(): String {
    let result = ''
    for (let i = this.number; i; --i) {
      result += `${i}<br/>\n`
    }
    return result + this.message
  }
}
