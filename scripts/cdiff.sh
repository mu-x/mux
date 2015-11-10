#!/bin/bash
#
# [C=2] mux-cdiff [SRING1] [STRING2]
#   Diffs charaters by $C blocks in strings
#

set -e
[ "$X" ] && set -x

COUNT=${C:-2}

LEFT=/tmp/mux-cdiff-$(uuidgen)
RIGHT=/tmp/mux-cdiff-$(uuidgen)

DOTS=$(printf "%0.s." $(seq 1 $COUNT))
PATTERN="s/\($DOTS\)/\1\n/g"

sed -e "$PATTERN" <<< "$1" > $LEFT
sed -e "$PATTERN" <<< "$2" > $RIGHT

diff $LEFT $RIGHT
rm $LEFT $RIGHT
