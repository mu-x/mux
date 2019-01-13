<template>
  <a v-on:click="click()">
    <img :src="previewUrl()" alt="preview" />
    <br>
    <b>{{ name }}</b>
    <br>
    {{ type == 'directory' ? 'open directory' : `download ${size}` }}
  </a>
</template>

<script>
import { makeLink } from './Api.js'

export default {
  name: 'Item',
  props: [
    'name',
    'type',
    'size',
    'path',
    'openDirectory',
  ],
  methods: {
    click() {
      if (this.type == 'directory')
        return this.openDirectory()
      
      console.log('Open', this.path, 'in new window')
      window.open(makeLink('content', this.path))
    },
    previewUrl() {
      switch (this.type) {
        case 'directory': return '/images/directory.png'
        case 'image': return makeLink('preview', this.path)
        default: return '/images/file.png'
      }
    }
  }
}
</script>
