"use strict"

const debug = require('debug')('webfs:file_system')

const fs = require('fs-extra')
const mimeTypes = require('mime-types')
const path = require('path')
const prettySize = require('prettysize')
const sharp = require('sharp')

const {ConcurrentTasks} = require('../server/utils.js')

class FileSystem {
  constructor(root, preview = {}) {
    this.root = root
    this.cache = preview.cache || path.join(this.root, '.webfs_previews')
    this.previewOptions = {size: 128, format: 'png', bg: {r: 0, g: 0, b: 0, alpha: 0}, ...preview}
    this.previewsInProgress = new ConcurrentTasks()

    console.info('Using cache directory:', this.cache)
    if (!fs.existsSync(this.cache)) { //< TODO: Switch to async versions.
      fs.mkdirSync(this.cache)
    }
  }

  async stop() {
    // No way to stop these tasks, only wait for completion...
    await this.previewsInProgress.waitAll()
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

    debug(`Stat for '${osPath}':`, item)
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

    debug(`Directory '${osPath}' contains ${items.length} items (${records.length} records)`)
    return items
  }

  async content(subPath) {
    const osPath = path.join(this.root, subPath)
    const content = await fs.readFile(osPath)
    const type = mimeTypes.lookup(osPath) || 'application/octet-stream'
    debug(`File '${osPath}' (${type}) read returns ${content.length} bytes`)
    return {type, content}
  }

  async preview(subPath) {
    const {format} = this.previewOptions
    const previewPath = path.join(this.cache, encodeURIComponent(subPath)) + `.${format}`
    const type = mimeTypes.lookup(previewPath).split(';')[0]
    if (await fs.exists(previewPath)) {
      debug(`Preview for '${subPath}' from cache '${previewPath}' (${type})`)
      return {type: type, content: await fs.readFile(previewPath)}
    }

    return await this.previewsInProgress.start(`Preview for ${subPath}`, async () => {
      const preview = await this.generatePreview(subPath)
      try {
        // For performance reasons the it does not make any sense to vate for file writing,
        // unfirtunallely there is no way to waut for this callback on exit yet.
        await fs.writeFile(previewPath, preview)

        debug(`Preview for '${subPath}' is saved to '${previewPath}'`)
      } catch (error) {
        console.error(`Preview for '${subPath}' failed to save to '${previewPath}'`)
      }

      return {type: type, content: preview}
    })
  }

  async generatePreview(subPath) {
    const type = this.type(subPath)
    switch (type) {
      case 'image': {
        const {size, format, bg} = this.previewOptions
        return await sharp(path.join(this.root, subPath))
          .resize(size, size, {background: bg, fit: 'contain'})
          .toFormat(format).toBuffer()
      }
      default: {
        throw new Error(`Unsupported preview format ${type} of '${subPath}'`)
      }
    }
  }
}

module.exports = FileSystem
