#!/usr/bin/env python

import json
import os
from pprint import pformat


class ParserError(Exception):
    pass


def parse(text, input_format='yaml'):  # types: (str, str) -> object
    if input_format in ('p', 'python'):
        from collections import *
        return eval(text)
    if input_format in ('y', 'yaml'):
        try:
            import yaml
        except ImportError:
            pass
        else:
            return yaml.load(text)
    return json.loads(text)


def expand(data, *args, **kwargs):  # types: (object, ...) -> object
    if isinstance(data, list):
        return [expand(v) for v in data]
    if isinstance(data, dict):
        return {k: expand(v) for k, v in data.items()}
    try:
        parsed = parse(data, *args, **kwargs)
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
    parser.add_argument('inputs', nargs='*')
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
            data = expand(data, args.expand_format)
        return serialize(data, args.output_format)

    inputs = args.inputs or [sys.stdin.read()]
    if len(inputs) > 1:
        diff_contents([format_content(t) for t in inputs], args.diff_tool)
    else:
        print(format_content(inputs[0]))

