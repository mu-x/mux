"use strict";

const express = require('express')
const path = require('path')

const fileSystem = require('./file_system')

const router = express.Router()

router.get('/*', (req, res) => {
    const directoryPath = unescape(req.path.replace(/^\//g, ''))
    console.log('-----------dp', directoryPath)
    fileSystem.list(directoryPath)
        .then(list => {
            const items = list.map(({name, size, type}) => {
                if (type == 'directory') {
                    var link = name + '/'
                    var preview = '/images/directory.png'
                } else {
                    const itemPath = encodeURIComponent(path.join(directoryPath, name))
                    var link = path.join('/api/content', itemPath)
                    var preview = (type == 'image') 
                        ? path.join('/api/preview', itemPath)
                        : '/images/file.png'
                }
                return {name: name, title: type, link, preview}
            })
            if (directoryPath) {
                items.unshift({
                    name: '..', title: 'level up',
                    link: '..',//path.dirname(req.path), 
                    preview: '/images/directory.png'
                })
            }
            res.render('browser', {path: directoryPath, items})
        })
        .catch(error => {
            console.warn(`Unable to show directory: ${error}`)
            res.statusCode = 404
            res.render('browser', {path: directoryPath, message: 'Directory does not exist'})
        })
});

module.exports = router