#!/usr/bin/python

import os
import sys
import json
from argparse import ArgumentParser
from pprint import pprint, pformat


def trace(code, *args, **kwargs):
    print('> {} ='.format(code))
    pprint(eval(code, *args, **kwargs))

def main():
    p = ArgumentParser()
    p.add_argument('--verbose', '-v', action='count', default=0)
    trace('p.parse_args()', locals())


if __name__ == "__main__":
    main()
