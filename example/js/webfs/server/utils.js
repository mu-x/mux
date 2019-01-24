"use strict"

class ConcurrentTasks {
  constructor() {
    this.running = new Map()
  }

  start(name, task) {
    return new Promise((resolve, reject) => {
      const waiters = this.running.get(name)
      if (waiters) {
        waiters.push({resolve, reject})
        console.debug(`Task '${name}' is running, handler is added to waiters: ${waiters.length}`)
        return 
      }

      this.running.set(name, [{resolve, reject}])
      const finish = (result) => {
        const waiters = this.running.get(name)
        this.running.delete(name)
        const printResult = () =>
          (['string', 'number'].includes(typeof result) || result instanceof Error) ? result : '?'

        console.debug(`Task '${name}' result '${printResult()}', notify ${waiters.length} waiters`)
        if (result instanceof Error) {
          waiters.forEach(w => w.reject(result))
        } else {
          waiters.forEach(w => w.resolve(result))
        }
      }

      console.debug(`Task '${name}' is started`)
      task().then(finish).catch(finish)
    })
  }

  waitAll() {
    if (!this.running.size) {
      console.debug('No tasks to wait, exiting')
      return new Promise((resolve) => resolve())
    }

    console.debug(`Wating for ${this.running.size} tasks`)
    return Promise.all(
      Array.from(this.running.values()).map(waiters => 
        new Promise((resolve, reject) => {
          console.debug(`All ${this.running.size} tasks finished`)
          waiters.push({resolve, reject})
        })
    ))
  }
}

module.exports = {ConcurrentTasks}