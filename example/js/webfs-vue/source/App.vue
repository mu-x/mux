<template>
  <div id="app">
    <div class="ribbon"><h1>Web FS</h1></div>
    <FileBrowser path="" />
    <div class="ribbon">
      See <a href="https://github.com/mu-x/mux">https://github.com/mu-x/mux</a>
    </div>
  </div>
</template>

<script>
import FileBrowser from './components/FileBrowser.vue'

export default {
  name: 'app',
  components: {
    FileBrowser
  }
}
</script>

<style>
#app {
  color: lightgrey;
  background-color: black;
}
* {
  margin: 0;
  padding: 0;
}
a {
  color: white;
  text-decoration: none;
}
a:hover {
  color: lightgrey;
}
.ribbon {
  text-align: center;
  background-color: rgb(101, 0, 128);
}
</style>
