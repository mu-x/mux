"use strict"

const startServer = require('./server/server.js')

// TODO: Add support for command line arguments and config file.
startServer({
    port: process.env.PORT || 8081,
    root: process.env.PATH || process.env.HOME || '.',
})
