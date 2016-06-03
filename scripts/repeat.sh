#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Repeats command every second until Ctrl+C
[L=inf] [D=1s] mux-repeat COMMAND [ARGS...]
END
exit 0; fi

set -e
[ "$X" ] && set -x

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
