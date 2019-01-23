"use strict"

const fs = require('fs-extra')
const path = require('path')
const prettySize = require('prettysize')
const mimeTypes = require('mime-types')
const sharp = require('sharp')

class FileSystem {
    constructor(options) {
        this.root = options.root
        this.cache = options.cache || path.join(this.root, '.webfs_previews')
        this.previewsInProgress = new Set()
        this.previewOptions = {
            size: 128, format: 'png', bg: {r: 0, g: 0, b: 0, alpha: 0},
            ...(options.preview || {})
        }

        console.log('Using cache directory:', this.cache)
        if (!fs.existsSync(this.cache)) { //< TODO: Switch to async versions.
            fs.mkdirSync(this.cache)
        }
    }

    type(subPath) {
        const type = mimeTypes.lookup(subPath)
        return (!type || type == 'application/octet-stream') ? 'unknown' : type.split('/')[0]
    }

    async stats(subPath) {
        const osPath = path.join(this.root, subPath)
        var item = {name: path.basename(subPath)}
        try {
            const stats = await fs.stat(await fs.realpath(osPath))
            if (stats.isDirectory()) {
                item.type = 'directory'
            } else {
                item.type = this.type(subPath)
                item.size = prettySize(stats.size)
            }
        } catch (error) {
            console.warn(`Unable to stat '${osPath}': ${error}`)
            item.type = 'error'
        }

        console.debug(`Stat for '${osPath}':`, item)
        return item
    }

    async list(subPath) {
        const osPath = path.join(this.root, subPath)
        const records = (await fs.readdir(osPath))
        const items = (
                await Promise.all(records.map(
                    async item => await this.stats(path.join(subPath, item)))
            ))
            .filter(item => !item.name.startsWith('.') && item.type != 'error')
            .sort((left, right) => {
                if (left.type == 'directory' && right.type != 'directory')
                    return -1
                if (left.type != 'directory' && right.type == 'directory')
                    return 1
                return left.name.localeCompare(right.name)
            })

        console.log(
            `Directory '${osPath}' contains ${items.length} items (${records.length} records)`)

        return items
    }

    async content(subPath) {
        const osPath = path.join(this.root, subPath)
        const content = await fs.readFile(osPath)
        console.log(`File '${osPath}' read returns ${content.length} bytes`)
        return content
    }

    async preview(subPath) {
        const {format} = this.previewOptions
        const previewPath = path.join(this.cache, encodeURIComponent(subPath)) + `.${format}`
        if (await fs.exists(previewPath)) {
            console.debug(`Preview for '${subPath}' from cache '${previewPath}'`)
            return fs.readFile(previewPath)
        }

        const preview = await this.makePreview(subPath)
        console.time(`Generating preview for '${subPath}'`)
        if (!this.previewsInProgress.has(preview)) {
            this.previewsInProgress.add(preview)
            try {
                // For performance reasons the it does not make any sense to vate for file writing,
                // unfirtunallely there is no way to waut for this callback on exit yet.
                await fs.writeFile(previewPath, preview)
                console.log(`Preview for '${subPath}' is saved to '${previewPath}'`)
            } catch (error) {
                console.error(`Preview for '${subPath}' failed to save to '${previewPath}'`)
            }
            this.previewsInProgress.delete(preview)
        }

        console.timeEnd(`Generating preview for '${subPath}'`)
        return preview
    }

    async makePreview(subPath) {
        if (this.type(subPath) == 'image') {
            const {size, format, bg} = this.previewOptions
            return await sharp(path.join(this.root, subPath))
                .resize(size, size, {background: bg, fit: 'contain'})
                .toFormat(format).toBuffer()
        }
        throw new Error(`Unsupported preview format ${type} of ${subPath}`)
    }
}

module.exports = FileSystem
