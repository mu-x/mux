#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Renices processes matching patterns.
Usage:
    [P=100] [FG=1] [D=10s] $0 [PATTERNS]
END
exit 0; fi

set -e
[ "$X" ] && set -x

PRIORITY=${P:-100}
PROCESSES=${@:-$MUX_RENICE_PROCESSES}
DELAY=${D:-10s}

if [[ $FG != 1 ]]; then
    P=$PRIORITY FG=1 D=$DELAY $0 $PROCESSES >/dev/null 2>&1 &
    exit 0
fi

while true; do
    renice $PRIORITY $(pidof $PROCESSES) || true
    sleep $DELAY
done
