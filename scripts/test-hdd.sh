#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Tests hdd for performance
[MIN=100M] [MAX=1G] [STEP=10] [BS=4M] [RUNS=3] [DIR=.] mux-test-hdd
END
exit 0; fi

set -e
[ "$X" ] && set -x

MIN=$(numfmt --from=iec ${MIN:-100M})
MAX=$(numfmt --from=iec ${MAX:-1G})
STEP=$(numfmt --from=iec ${STEP:-10})
BS=$(numfmt --from=iec ${BS:-4M})
RUNS=${RUNS:-3}
DIR=${DIR:-.}/$(uuidgen)

echo Test directory $DIR for sizes $(numfmt --to=iec $MIN)-$(numfmt --to=iec $MAX)
mkdir $DIR
trap "rm -rf $DIR" EXIT

size=$MIN
while (( size <= MAX )); do
    echo
    for run in $(seq 1 $RUNS); do
        fileName=$DIR/f$(uuidgen)
        dd if=/dev/urandom of=$fileName bs=$BS count=$(( size / BS )) \
            2>&1 | grep -v records #1>/dev/null 2>&1
        rm $fileName
    done
    (( size *= STEP ))
done

