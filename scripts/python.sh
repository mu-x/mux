#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Performs math operations by python from arguments or std in.
Usage: [CONF=VALUE] $0 [EXPRESSION]
Configuration:
    P interpretator, default: python
    M import modules (import M), default: sys, os
    I included modules (from I import *), default: math
    F from __future__ import {d=devision,w=with,u=unicode}
END
exit 0; fi

set -e
[ "$X" ] && set -x

PYTHON=${P:-python}
MODULES="sys os json $M"
INCLUDES="math datetime $I"

IMPORTS=
for module in $MODULES; do
    IMPORTS="import $module; $IMPORTS"
done
for module in $INCLUDES; do
    IMPORTS="from $module import *; $IMPORTS"
done

[[ "$F" == *d* ]] && IMPORTS="from __future__ import division; $IMPORTS"
[[ "$F" == *w* ]] && IMPORTS="from __future__ import with_statement; $IMPORTS"
[[ "$F" == *u* ]] && IMPORTS="from __future__ import unicode_literals; $IMPORTS"

if [[ "$@" ]]; then
    $PYTHON -c "$IMPORTS print($@)"
else
    cat <(echo -n "print(") <(cat) <(echo -n ")") | $PYTHON
fi
