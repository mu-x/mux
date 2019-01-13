<template>
  <div class="hello">
    <br>
    <a 
      v-for="(directory, index) in ['root'].concat(path)" 
      v-bind:key="directory" 
      v-on:click="clickPath(index)"
    >
      &nbsp; &gt; <b>{{ directory }}</b>
    </a>
    <h2 v-if="error">{{ error }}</h2>
    <div class="grid">
      <div class="grid-item" v-bind:key="item.name" v-for="item in items">
        <a v-on:click="clickItem(item.type, item.name)">
          <img :src="previewUrl(item.type, item.name)" alt="preview" />
          <br>
          <b>{{ item.name }}</b>
          <br>
          {{ item.type == 'directory' ? 'open directory' : `download ${item.size}` }}
        </a>
      </div>
    </div>
    <br>
  </div>
</template>

<script>
export default {
  name: 'FileBrowser',
  data() {
    return {
      path: [],
      error: '',
      items: []
    }
  },
  mounted() {
    this.openPath([])
  },
  methods: {
    clickPath(index) {
      this.openPath(this.path.slice(0, index))
    },
    clickItem(type, name) {
      if (type == 'directory')
        return this.openPath(this.path.concat([name]))
      
      window.open('/api/content/' + this.pathUrl(this.path.concat([name])))
    },
    openPath(path) {
      console.log('Reload path', path)
      fetch('/api/directory/' + this.pathUrl(path))
        .then(response => response.json())
        .then(items => {
          this.path = path
          this.items = items
        })
        .catch(error => {
          this.error = 'Unable to load directory content'
        })
    },
    pathUrl(path) {
      return path.map(item => encodeURIComponent(item)).join('/')
    },
    previewUrl(type, name) {
      switch (type) {
        case 'directory': return '/images/directory.png'
        case 'image': return '/api/preview/' + this.pathUrl(this.path.concat([name]))
        default: return '/images/file.png'
      }
    }
  }
}
</script>

<style scoped>
.grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(min-content, 200px));
}
.grid-item {
  padding: 10px;
  text-align: center;
}
</style>
