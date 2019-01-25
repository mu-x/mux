"use strict"

const Server = require('./server/server.js')

// TODO: Add support for command line arguments and config file.
const config = {
  port: process.env.PORT || 8081,
  root: process.env.ROOT || process.env.HOME || '.',
  production: process.env.NODE_ENV == 'production',
}
console.debug('Server config', config)

const server = new Server(config, port => console.info('Server is running on', port))
process.on('SIGINT', () => {
  console.info("Iterrupted by Ctrl+C, exiting...")
  server.stop().then(() => process.exit())
});
