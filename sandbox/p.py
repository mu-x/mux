#!/usr/bin/python

import sys, os
from contextlib import contextmanager

def trace(code, *args, **kwargs):
    print('{}:\n  {!r}'.format(code, eval(code, *args, **kwargs)))


def bool_generator(number):
    for _ in range(number):
        yield False
    yield True


def make_bool_call(number):
    g = bool_generator(number)
    return g.next


def retry_bool_call(number):
    bc = make_bool_call(number)
    while True:
        result = bc()
        if not result:
            yield result

def a(x=1, y=2):
    trace('x', locals())
    trace('y', locals())

def b(z=3, *args):
    trace('z', locals())
    a(*args)

def retry_bool_call_fancy(number):
    bc = make_bool_call(number)
    for result in retry(bc):
        yield Result


def main():
    trace('list(bool_generator(3))')

    bool_call = make_bool_call(3)
    trace('[bool_call() for _ in range(4)]', locals())

    trace('list(retry_bool_call(3))')
    b(1,2,3)

if __name__ == "__main__":
    main()
