"use strict";

const express = require('express')
const path = require('path')

const fileSystem = require('./file_system')

const router = express.Router()

router.get('/*', function(req, res) {
    const makeItem = (text, link, preview = []) => ({
        text: text, link: path.join.apply(this, link), 
        preview: preview.length ? path.join.apply(this, preview) : '/favicon.ico'
    })

    const directoryPath = unescape(req.path)
    const items = fileSystem.list(directoryPath).map(item => {
        const itemPath = path.join(directoryPath, item.name)
        return (item.type == 'directory')
            ? makeItem(item.name, [req.baseUrl, itemPath])
            : makeItem(item.name, ['/api/content', itemPath], ['/api/preview', itemPath])
    })

    if (directoryPath != '/')
        items.unshift(makeItem('..', [path.dirname(req.originalUrl)]))

    return res.render('browser', {path: req.path, items: items});
});

module.exports = router