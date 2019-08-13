import {Counter} from './counter.js'

let output = document.getElementById('output')
let c = new Counter(3, "Done!")
output.innerHTML += c.count()
