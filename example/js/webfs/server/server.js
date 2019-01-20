"use strict"

const express = require('express')
const logger = require('morgan')

const api = require('./api')

function startServer(config) {
  console.info('Server config:', config)

  const app = express()
  app.use(logger('dev'))
  
  app.use('/api', api(config))
  app.get('/browser', (req, res) => res.render('browser', {pathBase: '/browser'}))
  app.get('/', (req, res) => res.redirect('/browser'))

  app.set('view engine', 'ejs')
  app.set('views', __dirname)
  app.use(express.static('public'))
  
  if (process.env.NODE_ENV != 'production') {
      app.disable('etag')
  }
  
  const server = app.listen(config.port, () =>
    console.info(`Server is running on ${server.address().port}`))

  return server
}

module.exports = startServer