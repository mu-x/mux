"use strict";

const express = require('express')
const path = require('path')

const fileSystem = require('./file_system')

const router = express.Router()

router.get('/*', function(req, res) {
    const directory = req.params['0']
    return res.render('browser', {
        path: directory,
        backLink: path.dirname(directory),
        items: fileSystem.list(directory).map(item => {
            const itemPath = path.join(directory, item.name)
            return Object.assign(item, {
                link: (item.type == 'directory' ? '/' : '/api/content/') + itemPath,
                preview: '/api/prewiew' + itemPath,
            })
        })
    });
});

module.exports = router