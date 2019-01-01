"use strict";

const fs = require('fs')
const path = require('path')
const prettySize = require('prettysize')
const mime = require('mime-types')
const sharp = require('sharp')

class FileSystem {
    constructor(osPath, previewOptions={}) {
        this.osPath = osPath
        this.previewOptions = {
            cachePath: path.join(osPath, '.webfs_previews'),
            size: 128, format: 'png', bg: {r: 0, g: 0, b: 0, alpha: 0},
            ...previewOptions
        }
        try { 
            fs.mkdirSync(this.previewOptions.cachePath)
        } catch (error) {
            console.warn(`Warning: ${error}`)
        }
    }
    stats(subPath) {
        const osPath = path.join(this.osPath, subPath)
        var item = {name: path.basename(subPath)}
        try {
            const stats = fs.statSync(fs.realpathSync(osPath))
            item.type = stats.isDirectory() ? 'directory' : 'file'
            item.size = prettySize(stats.size)
        } catch (error) {
            console.error(`Unable to stat '${osPath}': ${error}`)
            item.type = 'error'
        }
        return item
    }
    async list(subPath) {
        return fs.readdirSync(await this.path(subPath))
            .filter(item => !item.startsWith('.'))
            .map(item => this.stats(path.join(subPath, item)))
            .filter(item => item.type != 'error')
    }
    async path(subPath) {
        return path.join(this.osPath, subPath)
    }
    async preview(subPath) {
        const {cachePath, format} = this.previewOptions
        const previewPath = path.join(cachePath, encodeURIComponent(subPath)) + `.${format}`
        console.log('preview', previewPath)
        if (!fs.existsSync(previewPath)) {
            const preview = await this.makePreview(subPath)
            await fs.writeFileSync(previewPath, await this.makePreview(subPath))
            console.log(`Preview '${previewPath}' is saved for '${subPath}'`)
        }
        return previewPath
    }
    async makePreview(subPath) {
        const type = mime.lookup(subPath) || 'unknown'
        if (type.startsWith('image')) {
            const {size, format, bg} = this.previewOptions
            return sharp(await this.path(subPath))
                .resize(size, size, {background: bg, fit: 'contain'})
                .toFormat(format).toBuffer()
        }
        throw new Error('Unsupported preview format ${type} of ${subPath}')
    }
}

module.exports = new FileSystem(process.env.ROOT || process.env.HOME)
