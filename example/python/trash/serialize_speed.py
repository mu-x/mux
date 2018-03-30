#!/usr/bin/env python3

import sys
import random
from time import time

import json
import yaml

def item(n, k, v):
    return dict(name=n, key=k, value=v)

def split_dump(d, f):
    for k, v in d.items():
        #l = '{name} {key} {value}\n'.format(**v)
        l = '{{"name":"{name}", "key":"{key} ,value:"{value}"}},\n'.format(**v)
        f.write(l)

def split_load(f):
    m = {}
    for l in f:
        try: n, k, v = l[:-1].split(' ')
        except: continue
        m[n] = item(n, k, v)
    return m

DRIVERS = {
    'split': (split_dump, split_load),
    'json-raw': (json.dump, json.load),
    'json-formated': (lambda d, f: json.dump(d, f, indent=2), json.load),
    'yaml-raw': (yaml.dump, yaml.load),
    'yaml-formated': (lambda d, f: yaml.dump(d, f, default_flow_style=False), yaml.load),
}

def name(prefix):
    return f'{prefix}{random.randint(0, 1000000000)}'

def make(number):
    m = {}
    for i in range(number):
        n = name('name')
        m[n] = item(n, name('key'), 777)
    return m

def path(driver):
    return f'./test_data.{driver}'

def main(number):
    data = make(int(number))
    print(f'Test {len(data)} records')
    for driver, dump_load in DRIVERS.items():
        print(f'{driver}:')
        dump, load = dump_load

        start = time()
        with open(path(driver), 'w') as f: dump(data, f)
        print(f'  write: {time() - start}')

        start = time()
        with open(path(driver), 'r') as f: assert len(data) == len(load(f))
        print(f'  read: {time() - start}')

if __name__ == '__main__':
    main(*sys.argv[1:])

