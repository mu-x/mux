#!/usr/bin/env python

import json


class ParserError(Exception):
    pass


def parse(text, input_format='yaml'):
    if input_format == 'yaml':
        try:
            import yaml
        except ImportError:
            pass
        else:
            return yaml.load(text)
    return json.loads(text)


def expand(data, *args, **kwargs):
    if isinstance(data, dict):
        return {k: expand(v) for k, v in data.items()}
    if isinstance(data, list):
        return [expand(v) for v in data.items()]
    try:
        return parse(data, *args, **kwargs)
    except Exception:
        return data


def serialize(data, output_format='yaml'):
    if output_format == 'yaml':
        try:
            import yaml
        except ImportError:
            pass
        else:
            return yaml.safe_dump(data, default_flow_style=False, width=1000)
    return json.dumps(data, indent=4, sort_keys=True)


def diff_contents(contents, diff_tool):
    command = [diff_tool]
    for index, content in enumerate(contents):
        name = '/tmp/mux-format.tmp.{}'.format(index)
        command.append(name)
        with open(name, "w") as f:
            f.write(content)
    os.system(' '.join(command))


if __name__ == '__main__':
    import argparse
    import os
    import sys

    parser = argparse.ArgumentParser()
    parser.add_argument('inputs', nargs='*')
    parser.add_argument('-d', '--diff-tool', default='diff')
    parser.add_argument('-i', '--input-format', default='yaml')
    parser.add_argument('-o', '--output-format', default='yaml')
    parser.add_argument('-r', '--recursive', type=bool, default='true')

    args = parser.parse_args()
    def format_content(text):
        try:
            data = parse(text, args.input_format)
        except Exception as e:
            return str(e)
        if args.recursive:
            data = expand(data)
        return serialize(data, args.output_format)

    inputs = args.inputs or [os.stdin.read()]
    if len(inputs) > 1:
        diff_contents([format_content(t) for t in inputs], args.diff_tool)
    else:
        print(format_content(inputs[0]))

