import Game from './gngn/game.js'
import {Rect, Text} from './gngn/visual.js'

export default function run(canvas) {
  let game = new Game(canvas)
  game.world.addChildren(
    new Rect('red', canvas.width, canvas.height),
    new Text('blue', '30px Arial', 'Hello World!'),
  )
  game.run()
}
