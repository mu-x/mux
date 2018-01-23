#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Performs math operations by python from arguments or std in.
Usage: [CONF=VALUE] $0 [EXPRESSION]
Configuration:
    P interpretator, default: python
    M import modules (import M), default: sys, os
    I included modules (from I import *), default: math
    F from __future__ import {d=devision,w=with,u=unicode}, default: d
END
exit 0; fi

set -e
[ "$X" ] && set -x

PYTHON=${P:-python}
MODULES="sys os json $M"
INCLUDES="math datetime $I"
FUTURE=${F:-d}

IMPORTS=
for module in $MODULES; do
    IMPORTS="import $module; $IMPORTS"
done
for module in $INCLUDES; do
    IMPORTS="from $module import *; $IMPORTS"
done

[[ "$FUTURE" == *d* ]] && IMPORTS="from __future__ import division; $IMPORTS"
[[ "$FUTURE" == *w* ]] && IMPORTS="from __future__ import with_statement; $IMPORTS"
[[ "$FUTURE" == *u* ]] && IMPORTS="from __future__ import unicode_literals; $IMPORTS"

function run_python() {
    $PYTHON -c "$IMPORTS print($@)"
}

if [[ "$@" ]]; then
    run_python "$@"
else
    while read LINE; do run_python "$LINE"; done
fi
