#!/usr/bin/env python

import json
import os
from collections import *
from pprint import pformat

LIST_TO_DICT_KEYS = ['name', 'id']


class ParserError(Exception):
    pass


def parse(text, input_format='yaml'):  # types: (str, str) -> object
    if input_format in ('p', 'python'):
        return eval(text)
    if input_format in ('y', 'yaml'):
        try:
            import yaml
        except ImportError:
            pass
        else:
            return yaml.load(text)
    return json.loads(text)


def expand(data, list_to_dict=False, *parse_args, **parse_kwargs
        ):  # types: (object, ...) -> object
    """Tries to parse string values recurcively.
        :list_to_dict Enables conversions [{name: NAME, ...}, ...] to [{NAME: ...}, ...]
    """
    expand_ = lambda d: expand(d, list_to_dict, *parse_args, **parse_kwargs)
    if isinstance(data, list):
        expanded = [expand_(v) for v in data]
        if not list_to_dict:
            return expanded
        def dict_eject(d, key):
            md = {k: v for k, v in d.items() if k != key}
            return md['value'] if list(md.keys()) == ['value'] else md
        def dict_item(d):
            for key in LIST_TO_DICT_KEYS:
                if key in d:
                    return d['name'], dict_eject(d, key)
        try:
            return {k: expand_(v) for k, v in map(dict_item, expanded)}
        except Exception as e:
            pass

    if isinstance(data, dict):
        return {k: expand_(v) for k, v in data.items()}

    try:
        parsed = parse(data, *parse_args, **parse_kwargs)
        if isinstance(parsed, dict) and len(parsed) == 1 and parsed.values() == [None]:
            return data  # Avoid accidental dict syntax.
        return parsed
    except Exception:
        return data


def serialize(data, output_format='yaml'):  # types: (object, str) -> str
    if output_format in ('p', 'python'):
        return pformat(data)
    if output_format in ('y', 'yaml'):
        try:
            import yaml
        except ImportError:
            pass
        else:
            return yaml.safe_dump(data, default_flow_style=False, width=1000)
    return json.dumps(data, indent=4, sort_keys=True)


def diff_contents(contents, diff_tool):  # types: (List[str], str) -> None
    command = [diff_tool]
    for index, content in enumerate(contents):
        name = '/tmp/mux-format.tmp.{}'.format(index)
        command.append(name)
        with open(name, "w") as f:
            f.write(content)
    os.system(' '.join(command))


if __name__ == '__main__':
    import argparse
    import sys

    parser = argparse.ArgumentParser()
    parser.add_argument('inputs', nargs='*', help=', '.join([
        'empty - format stdin',
        'single - format file or text',
        'multi - format files or texts & diff them',
    ]))
    parser.add_argument('-l', '--list-to-dict', action='store_true', default=False)
    parser.add_argument('-d', '--diff-tool', default='diff')
    parser.add_argument('-e', '--expand-format', default='json')
    parser.add_argument('-i', '--input-format', default='yaml')
    parser.add_argument('-o', '--output-format', default='yaml')

    args = parser.parse_args()
    def format_content(text_or_file):
        try:
            with open(text_or_file) as f:
                text = f.read()
        except IOError:
            text = text_or_file
        try:
            data = parse(text, args.input_format)
        except Exception as e:
            return str(e)
        if args.expand_format:
            data = expand(data, args.list_to_dict, args.expand_format)
        return serialize(data, args.output_format)

    inputs = args.inputs or [sys.stdin.read()]
    if len(inputs) > 1:
        diff_contents([format_content(t) for t in inputs], args.diff_tool)
    else:
        print(format_content(inputs[0]))

