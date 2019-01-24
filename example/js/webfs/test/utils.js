"use strict"

const assert = require('assert')

const {ConcurrentTasks} = require('../server/utils.js')

function timer(handler, timeout = 10) {
  return new Promise((resolve, reject) => setTimeout(() => {
    try { resolve(handler()) }
    catch(error) { reject(error) }
  }, timeout))
}

describe('ConcurrentTasks', () => {
  var counter = 0
  beforeEach(() => counter = 0)

  it('single execution', async () => {
    const tasks = new ConcurrentTasks()

    const results = await Promise.all([1, 2, 3].map(
      i => tasks.start('t1', timer.bind(this, () => counter += 1))
    ))

    results.forEach(i => assert.equal(i, 1))
    assert.equal(counter, 1)

    await tasks.waitAll()
    assert.equal(counter, 1)
  })

  it('different tasks', async () => {
    const tasks = new ConcurrentTasks()

    const results = await Promise.all([1, 2, 3].map(
      i => tasks.start(`t${i}`, timer.bind(this, () => counter += 1))
    ))

    assert.equal(results.reduce((a, b) => a + b), 1 + 2 + 3)
    assert.equal(counter, 3)

    await tasks.waitAll()
    assert.equal(counter, 3)
  })

  it('wait all', async () => {
    const tasks = new ConcurrentTasks()

    tasks.start('t1', timer.bind(this, () => counter += 1))
    tasks.start('t1', timer.bind(this, () => counter += 1))
    tasks.start('t2', timer.bind(this, () => counter += 1))

    await tasks.waitAll()
    assert.equal(counter, 2)
  })

  it('throw error', async () => {
    const tasks = new ConcurrentTasks()

    try {
      await tasks.start('t', timer.bind(this, () => { throw Error("fuck") }))
      assert.fail('Exception is not thrown')
    } catch (error) {
      assert.equal(error.toString(), 'Error: fuck')
    }

    await tasks.waitAll()
  })
})