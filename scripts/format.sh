#!/bin/bash
#
# [F=json] mux-format [TEXT...]
#   Formats input text as F
#

set -e
[ "$X" ] && set -x

FORMAT=${F:-json}
LINES=${L:-$(tput lines)}

IN="$@"
if [ ! "$IN" ]; then
   IN=$(cat <&0)
fi
case $FORMAT in
    j|json)
        FORMATER='python -m json.tool'
        ;;
    x|xml)
        FORMATER='xmllint --format'
        ;;
    *)
        echo Error: unknown format: $FORMAT
        exit 2
esac

OUT=$(echo $IN | $FORMATER)
LENGTH=$(echo "$OUT" | wc -l)

if [ "$LENGTH" -ge "$LINES" ]; then
    echo "$OUT" | vi -
else
    echo "$OUT"
fi
