module.exports = {
  outputDir: 'dist_vue',
  lintOnSave: true,
  configureWebpack: {
    resolve: {
      alias: {
        '@': __dirname + '/source'
      }
    },
    entry: {
      app: './source/main.js'
    }
  }
}