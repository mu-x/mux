"use strict";

const express = require('express')
const path = require('path')
const logger = require('morgan')

const api = require('./server/api')
const browser = require('./server/browser')

const app = express()
app.use(logger('dev'))

app.use('/api', api)

// HTML based pages
app.use('/', browser)
app.set('view engine', 'ejs')
app.set('views', path.join(__dirname, 'server'))

// TODO: Move to config?
const port = process.env.PORT || 8080
app.listen(port, () => console.log('Running on ' + port))