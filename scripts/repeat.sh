#!/bin/bash
#
# [L=inf] [D=1s] mux-repeat COMMAND [ARGS...]
#   Repeats command every second until Ctrl+C
#

set -e

COMMAND=$@
LIMIT=${L:-inf}
DELAY=${D:-1s}

if [ ! "$COMMAND" ]; then
    echo Command argument is mandatory!
    exit 1
fi

function onCtrlC {
    echo Interupted!
    exit 0
}
trap onCtrlC SIGINT

ITER=0
while [ "$ITER" != "$LIMIT" ]; do
    if [ "$S$V" ]; then
        echo
        echo $COMMAND
    fi

    $COMMAND
    sleep $DELAY
    (( ITER++ )) || true
done
