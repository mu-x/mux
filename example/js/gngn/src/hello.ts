import Game from './gngn/game.js'
import { Aligment, Sprite, Text, Rect } from './gngn/visual.js'
import { Point, Size } from './gngn/geometry.js';
import { Component } from './gngn/component.js';
import { ControllerMover, AutoMover } from './gngn/move.js';
import { Controller } from './gngn/controls.js';
import { Timer } from './gngn/utils.js';

export default function run(canvas: HTMLCanvasElement) {
  const carSpeed = 500
  const pedastrianSpawn = 1
  var laneWidth = canvas.height / 3
  var carSize = new Size({width: laneWidth * 1.5, height: laneWidth * 0.7})

  let game = new Game(canvas)
  new Sprite(game.world, game.image('images/road.png'), Aligment.CORNER, new Size(canvas))

  let player = new Component("player", game.world, {
    x: carSize.width, y: canvas.height / 2
  })
  new Rect(player, 'blue', carSize)
  new ControllerMover(player, new Controller(), {
    ArrowUp: {y: -carSpeed}, ArrowDown: {y: carSpeed},
    ArrowLeft: {x: -carSpeed}, ArrowRight: {x: carSpeed}
  })

  new Timer(game.world, pedastrianSpawn, () => {
    let p = new Component("pedastrian", game.world, {
      x: canvas.width + carSize.width, y: canvas.height / 2
    })
    new Rect(p, 'red', carSize)
    new AutoMover(p, new Point({x: -carSpeed}))
  })

  console.log("Start game:", game)
  game.run()
}
