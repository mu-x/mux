"use strict";

const express = require('express')
const path = require('path')

const fileSystem = require('./file_system')

const router = express.Router()

router.get('/*', function(req, res) {
    const directory = req.params['0']
    var items = fileSystem.list(directory).map(item => {
        const itemPath = path.join(directory, item.name)
        return (item.type == 'directory')
            ? {link: itemPath, preview: 'favicon.ico', text: item.name}
            : {link: 'api/content/' + itemPath, preview: 'api/preview' + itemPath, text: item.name}
    })

    const parent = path.dirname(directory)
    if (parent)
        items.unshift({link: parent, preview: 'favicon.ico', text: '..'})

    return res.render('browser', {path: directory, items: items});
});

module.exports = router