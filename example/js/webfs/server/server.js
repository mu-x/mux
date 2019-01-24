"use strict"

const express = require('express')
const logger = require('morgan')

const FileSystem = require('./file_system')

class Server {
  constructor(config) {
    console.info('Server config:', config)
    this.fileSystem = new FileSystem(config)
    this.app = express()
    this.app.use(logger('dev'))

    this.app.get('/', (req, res) => res.redirect('/browser'))
    this.app.get('/browser', (req, res) => res.render('browser', {pathBase: '/browser'}))

    this.app.set('view engine', 'ejs')
    this.app.set('views', __dirname)

    this.app.use('/api', apiRouter(this.fileSystem))
    this.app.use(express.static('public'))
  
    if (process.env.NODE_ENV != 'production') {
      this.app.disable('etag')
    }
    
    this.listener = this.app.listen(config.port, () =>
      console.info(`Server is running on ${this.listener.address().port}`))
  }

  async stop() {
    console.log('Stopping server...')
    await this.listener.close()
    await this.fileSystem.stop()
    console.log('Server is stopped')
  }
}

function apiRouter(fileSystem) {
  const router = express.Router()

  router.route('/directory/*')
  .get(forwardGet(fileSystem, 'list'))

  router.route('/content/*')
    .get(forwardGet(fileSystem, 'content'))
    .post((request, response) => {
      response.statusCode = 404
      response.send('Not Implemented')
    })

  router.route('/preview/*')
    .get(forwardGet(fileSystem, 'preview'))

  return router
}

function forwardGet(target, method) {
  var getter = target[method].bind(target)
  return (request, response) =>
      getter(decodeURIComponent(request.params[0]))
          .then((content) => 
              response.send(content)
          )
          .catch((error) => {
              console.warn(error.toString())
              // TODO: Use other return codes for other situations.
              response.statusCode = 404
              response.send('Not Found')
          })
}

module.exports = Server