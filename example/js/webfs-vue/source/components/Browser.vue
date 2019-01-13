<template>
  <div class="hello">
    <br>
    <a 
      v-for="(directory, index) in ['root'].concat(path)" 
      v-bind:key="directory" 
      v-on:click="openPath(path.slice(0, index))"
    >
      &nbsp; &gt; <b>{{ directory }}</b>
    </a>
    <h2 v-if="error">{{ error }}</h2>
    <div class="grid">
      <div class="grid-item" v-bind:key="item.name" v-for="item in items">
        <Item
          :name="item.name" :type="item.type" :size="item.size"
          :path="path.concat([item.name])"
          :openDirectory="openPath.bind(this, path.concat([item.name]))"
        >
        </Item>
      </div>
    </div>
    <br>
  </div>
</template>

<script>
import { listDirectory } from './Api.js'
import Item from './Item.vue'

export default {
  name: 'Browser',
  components: {
    Item
  },
  data() {
    return {
      path: [],
      error: '',
      items: [],
    }
  },
  mounted() {
    this.openPath([])
  },
  methods: {
    openPath(path) {
      listDirectory(path)
        .then(items => {
          this.path = path
          this.items = items
        })
        .catch(error => {
          this.error = 'Unable to load directory content'
        })
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
