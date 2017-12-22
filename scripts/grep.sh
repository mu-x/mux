#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Grep in stream, file or directory skiping version control
Usage 1: $0 [OPTIONS] PATTERN [FILE|DIRECTORY]
Usage 2: cat FILE | $0 [OPTIONS] PATTERN
END
exit 0; fi

set -e
[ "$X" ] && set -x

PATTERN=$1
shift

if [ "$1" ] && [[ "$1" != -* ]]; then
    DIR=$1
    shift
else
    if [ -t 0 ]; then
        DIR=.
    else
        DIR=
    fi
fi

if [[ "$DIR" ]]; then
    if which ag 2>/dev/null; then
        ag "$PATTERN"
    else
        grep -rI "$PATTERN" "$DIR" "$@" --exclude-dir=".hg" --exclude-dir=".git"
    fi
else
    echo grep "$PATTERN"
fi
