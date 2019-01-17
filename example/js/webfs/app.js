"use strict"

const express = require('express')
const path = require('path')
const logger = require('morgan')

const api = require('./server/api')

const app = express()
app.use(logger('dev'))
app.set('view engine', 'ejs')
app.set('views', path.join(__dirname, 'server'))

app.use(express.static('public'))
app.use('/api/', api)
app.get('/', (req, res) => res.redirect('/browser'))
app.get('/browser', (req, res) => res.render('browser', {pathBase: '/browser'}))

if (process.env.DEBUG) {
    console.log('Enable DEBUG mode', process.env.DEBUG)
    app.disable('etag')
}

const port = process.env.PORT || 8081
app.listen(port, () => console.log('Running on ' + port))
