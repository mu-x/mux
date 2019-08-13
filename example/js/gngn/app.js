const express = require('express')

const app = express()
app.use('/', express.static('public'))
app.use('/', express.static('build'))

const port = process.env.PORT || 8080
app.listen(port, (err) => {
  if (err)
    console.log(`Unable to start server on ${port}:`, err)
  else
    console.log(`Server is running on ${port}`)
})
