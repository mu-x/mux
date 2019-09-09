"use strict"

const express = require('express')

let app = express()

app.use(express.static('public'))
app.get('/', (req, res) => res.redirect('/public/'))

app.get('/api/values', (req, res) => {
    function values(id, valueCount) {
        let v = {}
        for (let i = 0; i < valueCount; ++i) v[`value${i}`] = (id + 1) * 100 + i
        return v
    }
    function records(recordCount, valueCount) {
        let r = {}
        for (let id = 0; id < recordCount; ++id) r[`object${id}`] = values(id, valueCount)
        return r
    }
    let recordCount = parseInt(req.query.records) || parseInt(req.query.r) || 5
    let valueCount = parseInt(req.query.values) || parseInt(req.query.v) || 10
    console.log(`Generating ${recordCount} records with ${valueCount} values...`)
    res.send(records(recordCount, valueCount))
})

let port = process.env.PORT || 8080
app.listen(port, () => console.log(`Server is started on ${port}`))
