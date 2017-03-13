#!/usr/bin/python
'''ZombieAttack -- kivy based zombie shooter game!

Optimized for a touch screen, the main target platform Android 4+. However any
kivy platform is supported automatically.

Kivy runs on Linux, Windows, OS X, Android and iOS. -> http://kivy.org

Learn more: http://kivy-zombie-attack.googlecode.com
Download: http://code.google.com/p/kivy-zombie-attack/source/browse/
'''
import kivy
kivy.require('1.0.0')


from random import random, choice as rand_choice
from traceback import print_exc as trace_exception

# TODO: include some audio files bound to game events
from kivy.app import App
from kivy.clock import Clock
from kivy.logger import Logger
from kivy.properties import BooleanProperty, NumericProperty, StringProperty, \
    ObjectProperty, ListProperty
from kivy.uix.image import Image
from kivy.uix.label import Label
from kivy.uix.popup import Popup
from kivy.uix.widget import Widget


# TODO: merge this const stuff with *.kv file
UNIT_SCALE_X, UNIT_SCALE_Y = 20, 10
GAME_TEMPO = 1.0 / 60.0
ENEMY_PROBABILITY = 0.01 # 1%
ENEMY_COOLDOWN = 20


# TODO: remove during separation process
def trace(self, message, **kwargs):
    '''Traces [message] with [kwargs] as debug information
    '''
    name = 'ZA_%s' % type(self).__name__
    info = ['%s: %s' % (k, str(v)) for k, v in kwargs.iteritems()]
    Logger.debug('%s: %s %s' % (name, message, ', '.join(info)))


class Unit(Image):
    '''Base for any visible game object
    '''
    # TODO: fix image direction according to self.direction
    direction = NumericProperty(1)
    speed = NumericProperty()

    def on_direction(self, instance, value):
        '''Ensures that direction's [value] is 1 or -1 by scaling
        '''
        if abs(value) != 1:
            self.direction = 1 if value > 0 else -1


class Bullet(Unit):
    '''The Enimies killing unit, created by the Hero
    '''
    cooldown = NumericProperty()
    damage = NumericProperty()

    def step(self):
        '''Flies forward and disapears with zombie when collides
        '''
        for enemy in self.parent.enemies:
            if self.collide_widget(enemy):
                enemy.hp -= self.damage
                self.parent.hero.score += enemy.cost
                self.parent.remove_unit(self)
                return
        self.center_x += self.direction * self.speed


class Hero(Unit):
    '''Main game object controlled by a player
    '''
    move_req = BooleanProperty(False)
    fire_req = BooleanProperty(False)
    cooldown = NumericProperty()
    hp = NumericProperty()
    score = NumericProperty()

    def connect_label(self, label):
        '''Connects [label] to show Hero's hp and score
        '''
        def update_label(hero, value=None):
            label.text = 'HP %s, $ %s' % (hero.hp, hero.score)
            label.texture_update()
        self.bind(hp=update_label, score=update_label)
        update_label(self)

    def step(self):
        '''Moves and attacks if requested by control
        '''
        if self.hp <= 0:
            return self.parent.game_over(self.score)
        if self.move_req:
            self.center_x += self.direction * self.speed
        if self.cooldown:
            self.cooldown -= 1
        elif self.fire_req:
            bullet = Bullet(direction=self.direction, center=self.center)
            self.parent.add_unit(bullet)
            self.cooldown = bullet.cooldown
            self.fire_req = False


class Enemy(Unit):
    '''Base for any enemy in the game
    '''
    cost = NumericProperty()
    damage = NumericProperty()
    cooldown = NumericProperty()
    hp = NumericProperty()

    def step(self):
        '''Follows hero and attack him if collides
        '''
        if self.hp <= 0:
            return self.parent.remove_unit(self)
        if self.cooldown != 0:
            self.cooldown -= 1
        if self.collide_widget(self.parent.hero):
            if self.cooldown == 0:
                self.parent.hero.hp -= self.damage
                self.cooldown = ENEMY_COOLDOWN
        else:
            self.direction = self.parent.hero.center_x - self.center_x
            self.center_x += self.direction * self.speed


class Zombie(Enemy):
    '''Simple enemy'''
    pass

class Vampire(Enemy):
    '''A bit More dangerous enemy'''
    pass

POSSIBLE_ENEMYES = Zombie, Vampire


# TODO: implement keyboard aliases
class Control(Image):
    '''Base for onscreen touch control
    '''
    def on_touch_down(self, touch): self.on_touch(touch)
    def on_touch_move(self, touch): self.on_touch(touch)

    def on_touch(self, touch):
        '''Tries to calculate relative x, y and call [on_touch_relative] if ok
        '''
        x, y = touch.x - self.x, touch.y - self.y
        if (x > 0) and (x < self.width) and (y > 0) and (y < self.height):
            self.on_touch_relative(x, y)


class Arrows(Control):
    '''The Hero's movement Control buttons
    '''
    def on_touch_relative(self, x, y):
        self.parent.hero.direction = x - self.width / 2
        self.parent.hero.move_req = True
    def on_touch_up(self, touch):
        self.parent.hero.move_req = False


class Actions(Control):
    '''The Hero's fire and reload Control buttons
    '''
    def on_touch_relative(self, x, y):
        self.parent.hero.fire_req = True


class Level(Widget):
    '''Game scene
    '''
    hero = ObjectProperty(None)
    enemies = ListProperty(None)
    other = ListProperty(None)
    # interface:
    arrows = ObjectProperty(None)
    actions = ObjectProperty(None)
    label = ObjectProperty(None)

    def add_unit(self, unit):
        '''Adds the [unit] to the level
        '''
        self.add_widget(unit)
        unit.size = self.width / UNIT_SCALE_X, self.width / UNIT_SCALE_Y
        if isinstance(unit, Hero): self.hero = unit
        elif isinstance(unit, Enemy): self.enemies.append(unit)
        else: self.other.append(unit)

    def remove_unit(self, unit):
        '''Removes the [unit] fro the level
        '''
        self.remove_widget(unit)
        if isinstance(unit, Enemy): self.enemies.remove(unit)
        else: self.other.remove(unit)

    def step(self, dt):
        '''Invokes actions for each game object
        '''
        if not self.hero:
            self.add_unit(Hero(center=self.center))
            self.hero.connect_label(self.label)
        for unit in [self.hero] + self.enemies + self.other:
            try: unit.step()
            except StopIteration: trace_exception()
        if random() <= ENEMY_PROBABILITY:
           self.create_enemy()

    def create_enemy(self):
        '''Creates a random enemie
        '''
        cls = rand_choice(POSSIBLE_ENEMYES)
        x = rand_choice((self.x, self.x + self.width))
        self.add_unit(cls(center=(x, self.center_y)))

    def game_over(self, score):
        '''Ends the game and prints [score]
        '''
        msg = 'Zombies have eaten you brains, your result is $%s' % score
        pop = Popup(title='GAME OVER', content=Label(text=msg),
            size_hint=(None, None), size=(self.width / 2, self.height / 2))
        def exit_app(instance):
            raise SystemExit(0)
        pop.bind(on_dismiss=exit_app)
        pop.open()


class Application(App):
    '''ZombieAttack application
    '''
    def build(self):
        '''Creates game objects and returns the main one
        '''
        # TODO: implement menu and level creation + destroy stuff
        level = Level()
        Clock.schedule_interval(level.step, GAME_TEMPO)
        return level



if __name__ in ('__android__', '__main__'):
        Application().run()
