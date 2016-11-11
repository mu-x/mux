#!/bin/bash
if [[ "$1" == --help ]] || [[ "$1" == -h ]] || [[ ! "$1" ]]; then cat <<END
Poor man's profiler: https://poormansprofiler.org
Usage: [C=COUNT] [S=SLEEP] mux-poormansprofiler COMMAND
END
exit 0; fi

set -e
[ "$X" ] && set -x

COUNT=${C:-10}
SLEEP=${S:-1}

if [[ "$1" == '^[0-9]+$' ]]; then
    PID=$1
else
    PID=$(pgrep nx_network_ut | tail -1)
fi

for N in $(seq 1 $COUNT)
  do
    printf '\rAnalyzing process %s ... %s/%s' "$PID" "$N" "$COUNT" >&2
    gdb -ex "set pagination 0" -ex "thread apply all bt" -batch -p $PID || exit $?
    sleep $SLEEP
  done | \
awk '
  BEGIN { s = ""; }
  /^Thread/ { print s; s = ""; }
  /^\#/ { if (s != "" ) { s = s "," $4} else { s = $4 } }
  END { print s }' | \
sort | uniq -c | sort -r -n -k 1,1
echo >&2
