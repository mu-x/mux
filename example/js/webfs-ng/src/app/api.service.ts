import { Injectable } from '@angular/core'
import { HttpClient } from '@angular/common/http'

export interface Item {
  name: string,
  type: string,
  size: string,
  path: string[]
}

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  constructor(private http: HttpClient) {}

  listDirectory(path: string[]) {
    return this.http.get<Item[]>('/api/directory/' + path.join('/'))
  }

  downloadFile(path: string[]) {
    window.open('/api/content/' + path.join('/'))
  }

  previewPath(path: string[]) {
    return '/api/preview/' + path.join('/')
  }
}
