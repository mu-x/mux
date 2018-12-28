"use strict";

const express = require('express')

const fileSystem = require('./file_system')

const router = express.Router()

router.route('/directory/*')
    .get((req, res) => {
        res.json(fileSystem.list(req.params['0']))
    })
    .post((req, res) => {
        res.send('TODO')
    })

router.route('/content/*')
    .get((req, res) => {
        const file = fileSystem.read(req.params[0])
        res.header("Content-Type", file.type)
        res.send(file.data)
    })
    .post((req, res) => {
        res.send('TODO')
    });

router.route('/preview/*')
    .get((req, res) => {
        const file = fileSystem.read(req.params[0])
        if (file == null) {
            res.statusCode = 404
            res.send('Not Found')
        } else {
            res.header("Content-Type", file.type)
            res.send(file.data)
        }
    })

module.exports = router
