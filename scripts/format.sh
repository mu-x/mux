#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Formats input text as JSON or smth else
Usage: [F=json] mux-format [TEXT...] [< FILE_NAME]
END
exit 0; fi

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
