#!/usr/bin/python
'''Hanoi Towers

In the classic problem of the Towers of Hanoi, you have 3 rods and N disks of different
sizes which can slide onto any tower. The puzzle starts with disks sorted in ascending
order of size from top to bottom (e.g., each disk sits on top of an even larger one). You
have the following constraints:
    (A) Only one disk can be moved at a time.
    (B) A disk is slid off the top of one rod onto the next rod.
    (C) A disk can only be placed on top of a larger disk.

Write a program to move the disks from the first rod to the last using Stacks.
'''

import unittest

class Tower:
    class Error(Exception):
        pass

    def __init__(self, size=0):
        self.stack = list(xrange(size, 0, -1))

    def __repr__(self):
        return repr(self.stack)

    def __len__(self):
        return len(self.stack)

    def empty(self):
        return not self.stack

    def push(self, value):
        if self.stack and self.stack[-1] < value:
            info = value, str(self.stack)
            raise Tower.Error('Can not put %i to tower %s' % info)
        self.stack.append(value)

    def pop(self):
        if not self.stack:
            raise Tower.Error('Can not pop from empty tower')
        return self.stack.pop()


class HanoiTowers:
    def __init__(self, size=0):
        self.towers = (Tower(size), Tower(), Tower())

    def __repr__(self):
        return repr(self.towers)

    def __len__(self):
        total = 0
        for it in self.towers: total += len(it)
        return total

    def move(self, frm, to):
        self.towers[to].push(self.towers[frm].pop())

    def move_n(self, frm, to, count=None):
        count = count or len(self.towers[frm])
        if count == 1: return self.move(frm, to)
        free = list(set(range(3)) - {frm, to})[0]
        self.move_n(frm, free, count - 1)
        self.move(frm, to)
        self.move_n(free, to, count - 1)

    def not_empty(self):
        result = []
        for i in xrange(len(self.towers)):
            if not self.towers[i].empty():
                result.append(i)
        return tuple(result)


class TestHanoiTowers(unittest.TestCase):
    def test_tower(self):
        t = Tower(2)
        self.assertFalse(t.empty())
        self.assertEqual(t.pop(), 1)
        self.assertRaises(Tower.Error, t.push, 3)
        self.assertTrue(t.push(1) or True)
        self.assertEqual(t.pop(), 1)
        self.assertEqual(t.pop(), 2)
        self.assertRaises(Tower.Error, t.pop)
        self.assertTrue(t.empty())

    def test_towers_basic(self):
        t = HanoiTowers(5)
        self.assertEqual(t.not_empty(), (0, ))
        self.assertTrue(t.move(0, 1) or True)
        self.assertEqual(t.not_empty(), (0, 1))
        self.assertRaises(Tower.Error, t.move, 0, 1)

    def test_towers_move_n(self):
        for size in range(2, 15):
            t = HanoiTowers(size)
            self.assertEqual(t.not_empty(), (0, ))
            t.move_n(0, 1)
            self.assertEqual(t.not_empty(), (1, ))
            t.move_n(1, 2)
            self.assertEqual(t.not_empty(), (2, ))
            t.move_n(2, 0)
            self.assertEqual(t.not_empty(), (0, ))


if __name__ == '__main__':
    unittest.main()
