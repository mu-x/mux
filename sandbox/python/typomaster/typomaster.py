#!/usr/bin/python
'''Typomaster helps you improve your typing skills
'''

from xml.etree import ElementTree as xml

import curses
import random


class Error(Exception):
    pass


class Master:
    '''Typomaster Main Process Controller
    '''
    WRONG = 2

    class Exit(Exception):
        '''Master Exit Request
        '''
        def __repr__(self):
            return 'Exit: %s' % self.message

    def __init__(self, levels, level=1, quality=0.5):
        '''Creates fresh typemaster

        Arguments:
            levels -- level generator or list
            level -- start level number
        '''
        self.__level_iter = iter(levels)
        self.__quality = quality
        try:
            for i in xrange(1, level):
                self.__level_iter.next() # drop extra levels
        except StopIteration:
                raise Error('Not enought levels to start with %i', level)

        self.__screen = curses.initscr()
        curses.start_color()
        curses.init_pair(self.WRONG, curses.COLOR_WHITE, curses.COLOR_RED)

    def process(self):
        '''Runs typing process in the loop
        '''
        curses.noecho()
        curses.cbreak()

        try:
            self.__next_level()
            while True:
                self.__step()

        except KeyboardInterrupt:
            raise self.Exit('Exit by Ctrl+C request.')
        except Exception:
            raise

        finally:
            curses.echo()
            curses.nocbreak()
            curses.endwin()


    def __next_level(self, good_result=True):
        if good_result:
            try: self.__level = self.__level_iter.next()
            except StopIteration: raise self.Exit('The last level has gone!')
        self.__current = str()
        self.__screen.clear()
        self.__str('title', 0, '== TypoMasteR ==',
                   curses.color_pair(self.WRONG))
        self.__str('level', 0, self.__level)
        self.__print()

    def __step(self):
        key = self.__screen.getch()
        if key == 127: # BACKSPACE
            self.__current = self.__current[:-1]
        elif len(self.__level) == len(self.__current):
	        self.__next_level(self.__result >= self.__quality)
	        return
        elif len(unichr(key)) == 1:
            self.__current += unichr(key)
        self.__print()

    def __print(self):
        total, correct = len(self.__current), 0
        for i in xrange(total):
            attr = 0
            if self.__current[i] == self.__level[i]:
                correct += 1
            else:
                attr = curses.color_pair(self.WRONG)
            self.__str('current', i, self.__current[i], attr)

        if len(self.__level) != len(self.__current):
            self.__str('current', total, self.__level[total], curses.A_REVERSE)
            self.__str('current', total+1, self.__level[total+1:])

        self.__result = int(not total) or (float(correct) / total)
        self.__str('title', 30, 'Result: %2i / %2i = %0.2f, Border: %0.2f' % (
                    correct, total, self.__result, self.__quality))
        self.__screen.refresh()

    def __str(self, target, x, text, attr=0):
        target = {'title': 0, 'level': 1, 'current': 2, 'debug': 3}[target]
        self.__screen.addstr(target, x, text, curses.A_BOLD + attr)


def open_guide(guide='guide.en_US.xml', width=80, short=False, flat=False):
    '''Generates levels according guide file

    Arguments:
        guide -- xml guide file path
        width -- level length (default console 80 chars)
        short -- order to omit short 'new' levels
        flat -- order to not include spaces
    '''
    def make_row(char_set):
        if flat:
            used_set = char_set
        else:
            used_set = char_set + ' '
        chars = [random.choice(used_set) for i in xrange(width)]
        return ''.join(chars)

    levels=[]
    def read_one(tag):
        if 'new' in tag.attrib:
            return tag.attrib['new'], True
        if 'include' in tag.attrib:
            collector = ''
            for lvl in tag.attrib['include'].split(','):
                collector += levels[int(lvl)-1]
            return collector, False
        if 'upper' in tag.attrib:
            cont = levels[int(tag.attrib['upper'])-1].upper()
            for s, r in {',': '<', '.': '>', '/': '?'}.iteritems():
                cont = cont.replace(s, r)
            return cont, False

    for tag in xml.parse(guide).getroot():
        try:
            lvl, lvl_short = read_one(tag)
            levels.append(lvl)
            if not short or not lvl_short:
                yield make_row(lvl)
        except IndexError, ValueError:
            raise Error('Wrong level format: %s' & repr(tag.attrib))


def open_file(filename, width=80):
    '''Generates levels from file lines

    Arguments:
        filename -- name of file to open
        width -- level length (default console 80 chars)
    '''
    for line in open(filename):
        text = line.strip(' \t\n')
        while text:
            cut = text[:width]
            if len(cut) == width:
                lim = cut.rfind(' ')
                if lim == -1: lim = width
                cut = text[:lim]
            yield cut
            text = text[len(cut)+1:]


if __name__ == '__main__':
    print 'This file can be used only as module.'
