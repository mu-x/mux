"use strict";

const express = require('express')

const fileSystem = require('./file_system')

const router = express.Router()

function sendError(res, error) {
    console.warn(`Error: ${error}`)
    res.statusCode = 404
    res.send('Not Found')
}

router.route('/directory/*')
    .get((req, res) => fileSystem.list(decodeURIComponent(req.params[0]))
        .then((items) => res.send(items))
        .catch((error) => sendError(res, error))
    )

router.route('/content/*')
    .get((req, res) => fileSystem.path(decodeURIComponent(req.params[0]))
        .then((content) => res.sendFile(content))
        .catch((error) => sendError(res, error))
    )
    .post((req, res) => sendError('Not Tmplemented', res) //< TODO
    )

router.route('/preview/*')
    .get((req, res) => fileSystem.preview(decodeURIComponent(req.params[0]))
        .then((preview) => res.sendFile(preview))
        .catch((error) => sendError(res, error))
    )

module.exports = router
