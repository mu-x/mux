"use strict";

const express = require('express')
const path = require('path')
const logger = require('morgan')

const api = require('./server/api')
const browser = require('./server/browser')

const app = express()
app.use(logger('dev'))

app.use(express.static('public'))
app.use('/api', api)
app.use('/browser', browser)
app.get('/', (req, res) => res.redirect('/browser'))

app.set('view engine', 'ejs')
app.set('views', path.join(__dirname, 'server'))

const port = process.env.PORT || 8080
app.listen(port, () => console.log('Running on ' + port))
