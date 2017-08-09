#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Formats input text as JSON or smth else
Usage: [F=yaml|json|xml] mux-format [TEXT...] [< FILE_NAME]
END
exit 0; fi

set -e
[ "$X" ] && set -x

FORMAT=${F:-yaml}
LINES=${L:-$(tput lines)}

IN="$@"
if [ ! "$IN" ]; then
   IN=$(cat <&0)
fi

case $FORMAT in
    y|yaml)
        FORMATER='python -c'
        ARG="import sys, yaml; print yaml.safe_dump(yaml.load(sys.stdin), default_flow_style=False)"
        ;;
    j|json)
        FORMATER='python -m'
        ARG='json.tool'
        ;;
    x|xml)
        FORMATER='xmllint --format'
        ARG=''
        ;;
    *)
        echo Error: unknown format: $FORMAT
        exit 2
esac

OUT=$(echo $IN | $FORMATER "$ARG")
LENGTH=$(echo "$OUT" | wc -l)

if [ "$LENGTH" -ge "$LINES" ]; then
    echo "$OUT" | vi -
else
    echo "$OUT"
fi
