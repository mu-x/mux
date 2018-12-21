"use strict";

const express = require('express')
const mime = require('mime-types')

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
        const file = req.params['0']
        const type = mime.lookup(file)
        if (type) res.header("Content-Type", type);
        res.send(fileSystem.read(file))
    })
    .post((req, res) => {
        res.send('TODO')
    });

module.exports = router
