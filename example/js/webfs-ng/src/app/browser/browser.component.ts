import { Component, OnInit } from '@angular/core'

import { ApiService, Item } from '../api.service'

@Component({
  selector: 'app-browser',
  templateUrl: './browser.component.html',
  styleUrls: ['./browser.component.css']
})
export class BrowserComponent implements OnInit {
  private _path: string[]
  private _items: Item[]
  constructor(private _api: ApiService) {}

  ngOnInit() {
    this.updatePath([])
  }
  
  updatePath(path: string[]) {
    this._path = path
    this._items = []
    this._api.listDirectory(path).subscribe(items => { 
      console.log('Directory', path, 'updated with content', items)
      this._items = items.map(item => ({...item, path: this._path.concat(item.name)}))
    })
  }

  onPathClick(index: number) {
    this.updatePath(this._path.splice(0, index))
  }
 
  onItemClick(path: string[], type: string) {
    if (type == 'directory')
      this.updatePath(path)
    else
      this._api.downloadFile(path)
  }
}
