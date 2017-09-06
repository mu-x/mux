#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Tests hdd for performance
Usage: [MIN=100M] [MAX=10G] [STEP=10] [RUNS=3] [DIR=.] \\
     [BS=4M] [DEV=zero] [IF=/dev/\$DEV] $0
END
exit 0; fi

set -e
[ "$X" ] && set -x

MIN=$(numfmt --from=iec ${MIN:-100M})
MAX=$(numfmt --from=iec ${MAX:-10G})
STEP=$(numfmt --from=iec ${STEP:-10})
RUNS=${RUNS:-3}
DIR=${DIR:-.}/$(uuidgen)

BS=$(numfmt --from=iec ${BS:-4M})
DEV=${DEV:-zero}
IF=${IF:-/dev/$DEV}

echo Test directory $DIR with source $IF
mkdir $DIR
trap "rm -rf $DIR" EXIT

size=$MIN
while (( size <= MAX )); do
    echo
    for run in $(seq 1 $RUNS); do
        fileName=$DIR/f$(uuidgen)
        dd if=$IF of=$fileName bs=$BS count=$(( size / BS )) \
            2>&1 | grep -v records #1>/dev/null 2>&1
        rm $fileName
    done
    (( size *= STEP ))
done

