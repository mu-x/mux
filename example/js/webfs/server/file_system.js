"use strict";

const fs = require('fs')
const path = require('path')
const prettySize = require('prettysize');
const mime = require('mime-types')
const sharp = require('sharp')

class FileSystem {
    constructor(osPath) {
        this.osPath = osPath
    }
    stats(subPath) {
        const osPath = path.join(this.osPath, subPath)
        var item = {name: path.basename(subPath)}
        try {
            const stats = fs.statSync(fs.realpathSync(osPath))
            item.type = stats.isDirectory() ? 'directory' : 'file'
            if (stats.isDirectory())
                item.size = prettySize(stats.size)
        } catch (error) {
            console.log(`${error}`)
            item.type = 'error'
        }
        return item
    }
    list(subPath) {
        const osPath = path.join(this.osPath, subPath)
        const items = fs.readdirSync(osPath)
            .filter(item => !item.startsWith('.'))
            .map(item => this.stats(path.join(subPath, item)))
            .filter(item => item.type != 'error')

        console.log(`Found ${items.length} in ${osPath}`)
        return items
    }
    read(subPath) {
        const osPath = path.join(this.osPath, subPath)
        const type = mime.lookup(osPath)
        console.log(`Reading ${type} from ${osPath}`)
        return {type: type, data: fs.readFileSync(osPath)}
    }
    preview(subPath) {
        // TODO: Fix IT!
        const osPath = path.join(this.osPath, subPath)
        const imageType = mime.lookup(osPath)
        return sharp(osPath).resize(64, 64).toFormat('png').toBuffer().then((buffer) => {
            console.log(`Previewing ${imageType} (${buffer.byteLength} bytes) from ${osPath}`)
            return {type: imageType, promise: buffer}
        })
    }
}

module.exports = new FileSystem(process.env.ROOT || process.env.HOME)
