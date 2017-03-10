#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Performs math operations by python from arguments or std in.
Usage: [CONF=VALUE] mux-python [EXPRESSION]
Configuration:
    P interpretator, default: python
    M import modules (import M), default: sys, os
    I included modules (from I import *), default: math
END
exit 0; fi

set -e
[ "$X" ] && set -x

PYTHON=${P:-python}
MODULES="sys os $M"
INCLUDES=${P:-math}

IMPORTS=
for module in $MODULES; do
    IMPORTS="import $module; $IMPORTS"
done
for module in $INCLUDES; do
    IMPORTS="from $module import *; $IMPORTS"
done

if [[ "$@" ]]; then
    python -c "$IMPORTS print $@"
else
    cat | python
fi
