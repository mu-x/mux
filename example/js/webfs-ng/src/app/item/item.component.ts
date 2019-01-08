import { Component, Input, OnInit } from '@angular/core'

import { ApiService, Item } from '../api.service'

@Component({
  selector: 'app-item',
  templateUrl: './item.component.html',
  styleUrls: ['./item.component.css']
})
export class ItemComponent implements OnInit {
  @Input() data: Item
  @Input() parent: string[]
  private _previewUrl: string;
  constructor(private _api: ApiService) {}
  
  ngOnInit() {
    switch (this.data.type) {
      case 'directory': 
        this._previewUrl = '/assets/directory.png'
        break;
      case 'image':
        this._previewUrl = this._api.previewPath(this.parent.concat([this.data.name]))
        break;
      default:
        this._previewUrl = '/assets/file.png'
        break;
    }
  }
}
