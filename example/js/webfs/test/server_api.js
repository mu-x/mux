'use strict'

const fs = require('fs-extra')
const path = require('path')
const supertest = require('supertest')

const startServer = require('../server/server.js')

var direcotry, server
beforeEach(async () => {
  // TODO: Add support for OSs without /tmp.
  direcotry = `/tmp/webfs-test-${Math.random().toString().slice(2)}`
  await fs.copy(path.join(__dirname, 'data'), direcotry)
  server = startServer({port: 0, root: direcotry})
})

afterEach(async () => {
  server.close()
  await fs.remove(direcotry)
})

function preparePath(path) {
  return path.split('/').map(item => encodeURIComponent(item)).join('/')
}

describe('list directory', () => {
  ;[
    ['', [
      {name: 'Directory with spaces', type: 'directory', size: '4 kB'},
      {name: 'empty', type: 'directory', size: '4 kB'},
      {name: 'images', type: 'directory', size: '4 kB'},
      {name: 'previews', type: 'directory', size: '4 kB'},
      {name: 'Vary? strange& directory=', type: 'directory', size: '4 kB'},
      {name: 'text.txt', type: 'text', size: '5 Bytes'},
    ]],
    ['empty', []],
    ['images', [
      {name: 'kitten.jpg', type: 'image', size: '146.6 kB'},
      {name: 'petr.jpeg', type: 'image', size: '890 Bytes'},
      {name: 'puppy.jpg', type: 'image', size: '89.8 kB'},
    ]],
    ['previews', [
      {name: 'kitten.png', type: 'image', size: '20.3 kB'},
      {name: 'petr.png', type: 'image', size: '34.6 kB'},
      {name: 'puppy.png', type: 'image', size: '15.3 kB'},
    ]],
    ['Directory with spaces', [
      {name: 'hello world.txt', type: 'text', size: '12 Bytes'},
    ]],
    ['Vary? strange& directory=', [
      {name: 'another file', type: 'unknown', size: '12 Bytes'},
      {name: 'Is file?', type: 'unknown', size: '15 Bytes'},
      {name: 'part&of=url', type: 'unknown', size: '24 Bytes'},
    ]]
  ]
  .forEach(task => {
    const [requestPath, expectedData] = task
    it(requestPath, async () => {
      await supertest(server)
        .get('/api/directory/' + preparePath(requestPath))
        .expect(200)
        .expect(expectedData)
    })
  })
})

describe('list directory error', () => {
  ;[
    'no_such_directory',
    'text.txt', //< Is a file.
    'images/no_image'
  ]
  .forEach(requestPath => {
    it(requestPath, async () => {
      await supertest(server)
        .get('/api/directory/' + preparePath(requestPath))
        .expect(404)
        .expect('Not Found')
    })
  })
})

describe('content', () => {
  ;[
    'text.txt',
    'Vary? strange& directory=/Is file?',
    'Vary? strange& directory=/part&of=url',
    'Directory with spaces/hello world.txt',
    'images/kitten.jpg',
    'images/petr.jpeg',
  ]
  .forEach(requestPath => {
    it(requestPath, async () => {
      await supertest(server)
        .get('/api/content/' + preparePath(requestPath))
        .expect(200)
        .expect(await fs.readFile(path.join(__dirname, 'data', requestPath)))
    })
  })
})

describe('content error', () => {
  ;[
    'text2.txt',
    'Vary? strange& directory=/Is file??',
    'images/shrack.jpeg',
    'no_such_directry/puppy.jpeg',
  ]
  .forEach(requestPath => {
    it(requestPath, async () => {
      await supertest(server)
        .get('/api/content/' + preparePath(requestPath))
        .expect(404)
        .expect('Not Found')
    })
  })
})

describe('preview', () => {
  ;[
    'images/kitten.jpg',
    'images/puppy.jpg',
    'images/petr.jpeg',
  ]
  .forEach(requestPath => {
    it(requestPath, async () => {
      const previewName = `${path.basename(requestPath).split('.')[0]}.png`
      await supertest(server)
        .get('/api/preview/' + preparePath(requestPath))
        .expect(200)
        .expect(await fs.readFile(path.join(__dirname, 'data/previews', previewName)))
    })
  })
})

describe('preview error', () => {
  ;[
    'text.txt', //< Not an image.
    'no_such_file.jpeg',
    'images/no_such_file.jpeg',
    'no_such_directory/kitten.jpg',
  ]
  .forEach(requestPath => {
    it(requestPath, async () => {
      await supertest(server)
        .get('/api/preview/' + preparePath(requestPath))
        .expect(404)
        .expect('Not Found')
    })
  })
})