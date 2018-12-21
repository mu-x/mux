"use strict";

const fs = require('fs')
const path = require('path')
const prettySize = require('prettysize');

class FileSystem {
    constructor(osPath) {
        this.osPath = osPath
    }
    list(subPath) {
        const osPath = path.join(this.osPath, subPath)
        return fs.readdirSync(osPath)
            .filter(item => !item.startsWith('.'))
            .map(item => {
                const stats = fs.statSync(path.join(osPath, item))
                return {
                    name: item,
                    type: stats.isDirectory() ? 'directory' : 'file',
                    size: prettySize(stats.size),
                }
            })
    }
    read(subPath) {
        return fs.readFileSync(path.join(this.osPath, subPath))
    }
}

module.exports = new FileSystem(process.env.HOME)