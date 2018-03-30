#!/usr/bin/env python3

import os
import json
import logging

import yaml

logger = logging.getLogger(__name__)


class File:
    def __init__(self, *path):
        self.path = os.path.join(*path)

    def write(self, action, mode=''):
        """Executes an :action on a file, opened for writing.
        """
        with open(self.path, 'w' + mode) as f:
            action(f)

    def read(self, action, default=None, mode=''):
        """Executes an :action on a file, opened for writing.
        If file does not exist and default provided, it will be returned instead of an exception.
        """
        try:
            with open(self.path, 'r' + mode) as f:
                return action(f)
        except FileNotFoundError:
            if default is None: raise
            logger.warning('Read "{}" for non-existing file: {}'.format(default, self.path))
            return default

    def write_data(self, data, mode=''):
        self.write(lambda f: f.write(data), mode)

    def read_data(self, default=None, mode=''):
        return self.read(lambda f: f.read(), default, mode)

    def write_json(self, data):
        self.write(lambda f: json.dump(data, f))

    def read_json(self, default=None):
        return self.read(lambda f: json.load(f), default)

    def write_yaml(self, data):
        self.write(lambda f: yaml.dump(data, f))

    def read_yaml(self, default=None):
        return self.read(lambda f: yaml.load(f), default)

    def write_container(self, generator, brackets='{}'):
        opener, closer = brackets
        with open(self.path, 'w') as f:
            f.write(opener)
            try:
                f.write('\n' + next(generator))
                while True:
                    f.write(',\n' + next(generator))
            except StopIteration:
                f.write('\n' + closer)

    def parse(self):
        f = self.path.split('.')[-1].lower()
        if f == 'json':
            return self.read_json()
        if f == 'yaml':
            return self.read_yaml()
        raise NotImplemented('Unsupported format "{}" file: {}'.format(f, self.path))


class CacheSet(set):
    def __init__(self, *path):
        super().__init__()
        self._cache = File(*path)
        self.update(self._cache.read_json(set()))

    def save(self):
        self._cache.write_container(('"{}"'.format(i) for i in self), '[]')


class CacheDict(dict):
    def __init__(self, *path):
        super().__init__()
        self._cache = File(*path)
        self.update(self._cache.read_json(dict()))

    def save(self):
        self._cache.write_container('"{}": "{}"'.format(k, v) for k, v in self.items())

