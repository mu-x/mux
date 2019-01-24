"use strict"

const express = require('express')

const FileSystem = require('./file_system')

class Server {
  constructor(config) {
    console.info('Server config:', config)
    const {port, root, production, preview} = config
    this.fileSystem = new FileSystem(root, preview)

    this.app = express()
    this.app.use((req, res, next) => {
      next()
      console.log(`${req.method} ${req.url} -> ${res.statusCode}`)
    })

    this.app.get('/', (req, res) => res.redirect('/browser/'))
    this.app.get('/browser/*', (req, res) => 
      res.render('browser', {production, pathBase: '/browser'}))
    
    this.app.set('view engine', 'ejs')
    this.app.set('views', __dirname)

    this.app.use('/api', apiRouter(this.fileSystem))
    this.app.use(express.static('public'))
    this.app.use(express.static('node_modules/jquery/dist/'))
    this.app.use(express.static('node_modules/w3-css/'))

    if (!production) { 
      this.app.disable('etag')
    }
    
    this.listener = this.app.listen(port, () =>
      console.info(`Server is running on ${this.listener.address().port}`))
  }

  async stop() {
    console.info('Stopping server...')
    await this.listener.close()
    await this.fileSystem.stop()
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