"use strict"

class NavigationView {
  constructor(navigate) {
    this.element = $('#navigation')
    this.navigate = navigate
  }

  update(path) {
    const items = [''].concat(path.split('/').filter(i => i))
    console.debug('Update navigation view', items)
    this.element.html(items.map((item, index) =>
      $(`<span id="path${index}" class="button">${item || 'root'} /</span>`)
        .click(() => this.navigate(items.slice(0, index + 1).join('/')))
    ))
  }
}

class DirectoryView {
  constructor(navigate) {
    this.element = $('#directory')
    this.navigate = navigate
  }

  update(directory, items) {
    console.debug('Update directory view', directory, ':', items)
    this.element.html(items 
      ? items.map((item) => this.item(directory, item))
      : `Directory ${directory} is empty`
    )
  }

  error(error) {
    console.error('Error directory view: \n\n', error)
    this.element.html(`<span class="error">Unable to load directory</span>`)
  }

  item(directory, {name, type, size}) {
    const path = directory + name
    return $(`
      <span id="${name}" class="item">
        <div><img src="${this.preview(type, path)}" /></div>
        <div><b>${name}</b></div>
        <div>${size || 'directory'}</div>
      </span>
    `).click(() =>
      (type === 'directory') ? this.navigate(path) : window.open('/api/content/' + path)
    )
  }

  preview(type, path) {
    switch (type) {
      case 'image': return '/api/preview/' + path
      case 'directory': return '/images/directory.png'
      default: return '/images/file.png'
    }
  }
}

class Browser {
  constructor(pathBase) {
    this.pathBase = pathBase
    this.navigationView = new NavigationView(p => this.navigate(p))
    this.directoryView = new DirectoryView(p => this.navigate(p))
    this.navigate(window.location.pathname.substr(pathBase.length), /* pushState */ false)
  }

  navigate(path, pushState=true) {
    path = path + (path.endsWith('/') ? '' : '/')
    console.log('Navigate', path)
    if (pushState) {
      window.history.pushState(null, `WebFS: ${path}`, this.pathBase + path)
    }

    this.navigationView.update(path)
    fetch('/api/directory' + path)
      .then(res => res.json())
      .then(items => this.directoryView.update(path, items))
      .catch(error => this.directoryView.error(error))
  }
}
