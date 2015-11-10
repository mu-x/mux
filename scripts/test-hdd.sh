#!/bin/bash
#
# [S=1000] [T=1000000000] mux-test-hdd
#   Tests hdd for performance
#

set -e
[ "$X" ] && set -x

STEP=$(numfmt --from=iec ${S:-10K})
TOTAL=$(numfmt --from=iec ${T:-100M})
DIR=${D:-$( uuidgen )}

echo Test directory $DIR, total size $(numfmt --to=iec $TOTAL)
mkdir -p $DIR/copies
cd $DIR

function mk {
    local size=$1
    local total=0
    while (( total < TOTAL )); do
        dd if=/dev/urandom of=f$((total/size)) \
           bs=$SIZE count=$((size/SIZE)) \
              1>/dev/null 2>&1
        (( total += size ))
    done
}

function timer_exec {
    local timer=$(date +%s%N)
    $@
    local elapsed=$(( $(date +%s%N)  - timer ))
    echo $((elapsed/1000000)) msec for $1 $(numfmt --to=iec $2)
}

SIZE=$TOTAL
while (( SIZE >= STEP )); do
    timer_exec mk $SIZE
    rm -rf *
    (( SIZE /= STEP ))
done

cd ..
rmdir $DIR

