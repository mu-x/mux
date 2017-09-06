#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Plays ready sound until Ctrl+C
Usage: [FILE=SOUND] $0
END
exit 0; fi

set -e

DIR="$(dirname $(readlink -f "${BASH_SOURCE[0]}"))"
FILE=${F:-$DIR/resources/ready.wav}

echo Playing $FILE
trap "exit 0" INT
while :; do paplay "$FILE"; done
