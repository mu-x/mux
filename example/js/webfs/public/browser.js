"use strict"

const serverApi = {
  url(action, path) {
    return `/api/${action}${path}`
  },
  listDirectory(path) {
    return fetch(this.url('directory', path)).then(response => response.json())
  },
  preview(type, path) {
    switch (type) {
      case 'directory': return '/images/directory.png'
      case 'image': return this.url('preview', path)
      default: return '/images/file.png'
    }
  }
}

const browser = {
  pathBase: '',
  path: '',
  initialize(pathBase) {
    this.pathBase = pathBase
    this.navigate(window.location.pathname.substr(this.pathBase.length), false)
  },
  navigate(path, pushState=true) {
    this.path = path + (path.endsWith('/') ? '' : '/')
    console.log(`Navigate '${path}'`)
    if (pushState) {
      window.history.pushState(null, `WebFS: ${this.path}`, this.pathBase + this.path)
    }
    this.updateNavigation()
    serverApi.listDirectory(this.path)
      .then(items => this.updateBrowser(items))
      .catch(error => $('.browser').html(`Unable to load directory ${this.path}`))
  },
  updateNavigation() {
    const path = this.path.split('/').filter(i => i)
    path.unshift('')
    const renderButton = (item, index) => {
      const name = item || 'root'
      const target = path.slice(0, index + 1).join('/')
      return `<span class="w3-button" onClick="browser.navigate('${target}')">${name } /</span>`
    }
    $('.navigation').html(path.map(renderButton).join(''))
  },
  updateBrowser(items) {
    console.log('Render items', items)
    const renderItem = (item) => {
      const path = this.path + item.name
      const clickAction = (item.type === 'directory') 
        ? `browser.navigate('${path}')`
        : `window.open('${serverApi.url('content', path)}')`
      return `
        <div class="item w3-button" onClick="${clickAction}">
          <div><img class="preview" src="${serverApi.preview(item.type, path)}" /></div>
          <div><b>${item.name}</b></div>
          <div>[${(item.type == 'directory') ? 'open' : `download ${item.size}`}]</div>
        </div>
      `
    }
    $('.browser').html(items.map(renderItem).join(''))
  }
}