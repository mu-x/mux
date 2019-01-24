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

    this.app.get('/', (req, res) => res.redirect('/browser/'))
    this.app.get('/browser/*', (req, res) => res.render('browser', {pathBase: '/browser'}))

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
    .get((req, res) => 
      fileSystem.list(decodeURIComponent(req.params[0]))
        .then(content => res.send(content))
        .catch(error => {
          console.warn(error)
          res.status(404).send('Not Found')
        })
    )

  router.route('/content/*')
    .get((req, res) => 
      fileSystem.content(decodeURIComponent(req.params[0]))
        .then(({type, content}) => res.header('Content-Type', type).send(content))
        .catch(error => {
          console.warn(error)
          res.status(404).send('Not Found')
        })
    )
    .post((req, res) => 
      res.status(500).send('Not Implemented') // TODO: Implement!
    )

  router.route('/preview/*')
    .get((req, res) => 
      fileSystem.preview(decodeURIComponent(req.params[0]))
        .then(({type, content}) => {res.header('Content-Type', type).send(content)})
        .catch(error => {
          console.warn(error)
          res.status(404).send('Not Found')
        })
    )

  return router
}

module.exports = Server