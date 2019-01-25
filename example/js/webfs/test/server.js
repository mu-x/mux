'use strict'

const assert = require('assert')
const path = require('path')

const fs = require('fs-extra')
const supertest = require('supertest')

const Server = require('../server/server.js')
const {temporaryDirectory} = require('../server/utils.js')

describe('Server', () => {
  var direcotry, server
  
  beforeEach(async () => {
    direcotry = await temporaryDirectory(path.join(__dirname, 'data'))
    server = new Server({port: 0, root: direcotry})
  })

  afterEach(async () => { await server.stop() })

  function preparePath(path) {
    return path.split('/').map(item => encodeURIComponent(item)).join('/')
  }

  describe('list directory', () => {
    ;[
      ['', [
        {name: 'Directory with spaces', type: 'directory'},
        {name: 'empty', type: 'directory'},
        {name: 'images', type: 'directory'},
        {name: 'previews', type: 'directory'},
        {name: 'Vary+ strange& directory=', type: 'directory'},
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
      ['Vary+ strange& directory=', [
        {name: 'another file', type: 'unknown', size: '12 Bytes'},
        {name: 'Is file&', type: 'unknown', size: '15 Bytes'},
        {name: 'part&of=url', type: 'unknown', size: '24 Bytes'},
      ]]
    ]
    .forEach(task => {
      const [requestPath, expectedData] = task
      it(requestPath, async () => {
        await supertest(server.listener)
          .get('/api/directory/' + preparePath(requestPath))
          .expect('Content-Type', 'application/json; charset=utf-8')
          .expect(200, expectedData)
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
        await supertest(server.listener)
          .get('/api/directory/' + preparePath(requestPath))
          .expect(404)
          .expect('Not Found')
      })
    })
  })

  describe('content', () => {
    ;[
      ['text.txt', 'text/plain; charset=utf-8'],
      ['Vary+ strange& directory=/Is file&', 'application/octet-stream'],
      ['Vary+ strange& directory=/part&of=url', 'application/octet-stream'],
      ['Directory with spaces/hello world.txt', 'text/plain; charset=utf-8'],
      ['images/kitten.jpg', 'image/jpeg'],
      ['images/petr.jpeg', 'image/jpeg'],
    ]
    .forEach(data => {
      const [requestPath, contentType] = data
      it(requestPath, async () => {
        const expectedContent = await fs.readFile(path.join(__dirname, 'data', requestPath))
        await supertest(server.listener)
          .get('/api/content/' + preparePath(requestPath))
          .expect('Content-Type', contentType)
          .expect(200)
          // TODO: Find out how to fix supertest's warning. Unfortuatelly 'expect' is not an option
          //  because expect tries to parse text/plain as JSON (bug?). 
          .end((res) => assert.equal(res.body, expectedContent))
      })
    })
  })

  describe('content error', () => {
    ;[
      'text2.txt',
      'Vary+ strange& directory=/Is file&?',
      'images/shrack.jpeg',
      'no_such_directry/puppy.jpeg',
    ]
    .forEach(requestPath => {
      it(requestPath, async () => {
        await supertest(server.listener)
          .get('/api/content/' + preparePath(requestPath))
          .expect(404, 'Not Found')
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
        await supertest(server.listener)
          .get('/api/preview/' + preparePath(requestPath))
          .expect('Content-Type', 'image/png')
          .expect(200, await fs.readFile(path.join(__dirname, 'data', 'previews', previewName)))
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
        await supertest(server.listener)
          .get('/api/preview/' + preparePath(requestPath))
          .expect(404, 'Not Found')
      })
    })
  })
})