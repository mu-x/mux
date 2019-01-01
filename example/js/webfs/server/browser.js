"use strict";

const express = require('express')
const path = require('path')

const fileSystem = require('./file_system')

const router = express.Router()

router.get('/*', (req, res) => {
    const makeItem = (text, link, preview = []) => ({
        text: text, link: path.join.apply(this, link), 
        preview: preview.length ? path.join.apply(this, preview) : '/favicon.ico'
    })

    const directoryPath = unescape(req.path.replace(/^\//g, ''))
    fileSystem.list(directoryPath)
    .then(list => {
        const items = list.map(({name, size, type}) => {
            const itemPath = encodeURIComponent(path.join(directoryPath, name)).replace(/%2F/g, '/')
            return (type == 'directory')
                ? makeItem(name, [req.baseUrl, itemPath])
                : makeItem(`${name} (${size})`, ['/api/content', itemPath], ['/api/preview', itemPath])
        })

        if (directoryPath != '/')
            items.unshift(makeItem('..', [path.dirname(req.originalUrl)]))

        res.render('browser', {path: directoryPath, items: items})
    })
    .catch(error => {
        console.warn(`Unable to show directory: ${error}`)
        res.statusCode = 404
        res.render('browser', {path: directoryPath, message: 'Directory does not exist'})
    })
});

module.exports = router