#!/usr/bin/python
'''Typomaster helps you improve your typing skills

Usage:
    <this-script> [options] -- start typing process
    <this-script> --help    -- for more information
'''

import os
import optparse
import typomaster


def parse_args():
    '''Argument parsing for typomaster
    '''
    option_parser = optparse.OptionParser()
    def opt(*arg, **kw): option_parser.add_option(*arg, **kw)
    def_guide = os.path.dirname(typomaster.__file__) + '/guide.en_US.xml'

    opt('-g', '--guide', dest='guide', metavar='FILE', type='string',
        help='Guide file to train your skills', default=def_guide)

    opt('-l', '--level', dest='level', metavar='N', type='int',
        help='Difficulty level to start with', default=1)

    opt('-p', '--print-only', dest='print_only', action='store_true',
        help='Prints levels and exit (for debug guides)', default=False)

    opt('-q', '--quality', dest='quality', metavar='N', type='int',
        help='Bottom % of correct answers to level up', default=50)

    opt('-s', '--short-cut', dest='short_cut', action='store_true',
        help='Ommit short levels (for stronger users)', default=False)

    opt('-t', '--text', dest='text', metavar='FILE', type='string',
        help='Text file instead of guide to train', default='')

    opt('-w', '--width', dest='width', metavar='N', type='int',
        help='Row or level length', default=80)

    opt('-d', '--debug', dest='debug', action='store_true',
        help='Provides full output in case of errors', default=False)

    opt('-f', '--flat', dest='flat', action='store_true',
        help='Provides flat text levels (no spaces)', default=False)

    return option_parser.parse_args()


def main():
    opts, args = parse_args()
    levels = None

    if opts.text:
        levels = typomaster.open_file(opts.text, opts.width)
    else:
        levels = typomaster.open_guide(opts.guide, opts.width,
                                       opts.short_cut, opts.flat)

    if opts.print_only:
        number = opts.level
        for i in xrange(number - 1):
            levels.next()
        for line in levels:
            print("%2i: %s" % (number, line))
            number += 1;
        return

    master = None
    try:
        quality = float(opts.quality) / 100
        master = typomaster.Master(levels, opts.level, quality)
        master.process()
    except Exception, ex:
        if opts.debug: raise
        else: print ex

if __name__ == '__main__':
    main()
