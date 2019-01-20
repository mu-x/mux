"use strict"

const express = require('express')

const FileSystem = require('./file_system')

function api(options) {
    const router = express.Router()
    const fileSystem = new FileSystem(options)

    const forwardGet = getter => {
        const getterBind = getter.bind(fileSystem)
        return (request, response) =>
            getterBind(decodeURIComponent(request.params[0]))
                .then((content) => 
                    response.send(content)
                )
                .catch((error) => {
                    console.warn(error.toString())
                    // TODO: Use other return codes for other situations.
                    response.statusCode = 404
                    response.send('Not Found')
                })
    }

    router.route('/directory/*')
        .get(forwardGet(fileSystem.list))

    router.route('/content/*')
        .get(forwardGet(fileSystem.content))
        .post((request, response) => {
            response.statusCode = 404
            response.send('Not Implemented')
        })

    router.route('/preview/*')
        .get(forwardGet(fileSystem.preview))

    return router
}

module.exports = api
