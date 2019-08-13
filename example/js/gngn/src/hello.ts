import {Game, Component} from './gngn/game.js'
import {Aligment, Sprite, Text} from './gngn/visual.js'

export default function run(canvas: HTMLCanvasElement) {
  let game = new Game(canvas)
  game.world.addChildren(
    new Sprite(game.image('images/road.png'), game.screen, Aligment.CORNER),
    new Component(game.screen.center, new Text('Hello World!', 'blue', '30px Arial')),
  )
  game.run()
}
