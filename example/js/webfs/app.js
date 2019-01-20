"use strict"

const startServer = require('./server/server.js')

startServer({
    port: process.env.PORT || 8081,
    root: process.env.ROOT_PATH || process.env.HOME || '.',
})
