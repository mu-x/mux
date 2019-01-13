function _url(path) {
  return path.map(item => encodeURIComponent(item)).join('/')
}

export function listDirectory(path) {
  console.log('List directory', path, '...')
  return fetch('/api/directory/' + _url(path))
    .then(response => response.json())
    .then(items => {
      console.log('Directory', path, 'contains:', items)
      return new Promise((resolve, _) => resolve(
        items.map(item => ({...item, path: path.concat(name)}))
      ))
    })
}
  
export function makeLink(type, path) {
    return `/api/${type}/${_url(path)}`
}
