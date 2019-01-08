import React from 'react';

class Browser extends React.Component {
  state = {
    path: [],
    items: []
  }

  componentDidMount() {
    this.changePath([])
  }

  render() {
    return (
      <div>
        <div>
          <span><a onClick={ this.onPathClick.bind(this, 0) }>root/</a></span>
          { 
            this.state.path.map((item, index) => (
              <a onClick={ this.onPathClick.bind(this, index + 1) }>&nbsp; {item}/</a>
            )) 
          }
        </div>
        <div className="grid">
          {
            this.state.items.map(item => (
              <div className="grid-item">
                <a onClick={ this.onItemClick.bind(this, item) }>
                  <img src={ this.previewUrl(item) } alt="preview"/>
                  <br/><b>{ item.name }</b>
                  <br/>{ item.type } { item.size }
                </a>
              </div>
            ))
          }
        </div>
      </div>
    );
  }

  previewUrl(item) {
    switch (item.type) {
      case 'directory': return '/directory.png'
      case 'image': return '/api/preview/' + this.state.path.concat([item.name]).join('/')
      default: return '/file.png'
    }
  }

  onPathClick(index) {
    this.changePath(this.state.path.slice(0, index))
  }

  onItemClick(item) {
    let itemPath = this.state.path.concat([item.name])
    if (item.type == 'directory')
      return this.changePath(itemPath)

    console.log('Download file', itemPath)
    window.open('/api/content/' + itemPath.join('/'))
  }

  changePath(path) {
    console.log('Change path to', path)
    this.setState({path})

    const url = '/api/directory/' + path.join('/')
    fetch(url)
        .then(res => res.json())
        .then(items => this.setState({items}))
        .catch(error => console.error('Unable to fetch from', url, error))
  }
}

export default Browser;