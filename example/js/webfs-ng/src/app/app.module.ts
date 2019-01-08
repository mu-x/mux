import { BrowserModule } from '@angular/platform-browser'
import { NgModule } from '@angular/core'
import { HttpClientModule } from '@angular/common/http'

import { AppRoutingModule } from './app-routing.module'
import { AppComponent } from './app.component'
import { ItemComponent } from './item/item.component'
import { BrowserComponent } from './browser/browser.component'

import { ApiService } from './api.service'

@NgModule({
  declarations: [
    AppComponent,
    ItemComponent,
    BrowserComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    AppRoutingModule
  ],
  providers: [
    ApiService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
