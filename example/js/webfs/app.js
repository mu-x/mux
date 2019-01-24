"use strict"

const Server = require('./server/server.js')

// TODO: Add support for command line arguments and config file.
new Server({
  port: process.env.PORT || 8081,
  root: process.env.ROOT || process.env.HOME || '.',
  production: process.env.NODE_ENV == 'production',
})
