#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Rsync helper with preview and some other features.
Usage: [NO_DELETE=1] $0 SOURCE TARGET
END
exit 0; fi

set -e
[ "$X" ] && set -x

ARGS="--archive"
[ -z "$NO_DELETE" ] && ARGS+=" --delete"

LOG=/tmp/mux-rsync-$(date +%s)
echo Log file: "$LOG"
rsync $ARGS --verbose --dry-run --stats "$@" > "$LOG"
vi "$LOG"

IFS= read -p "Continue? (y/n): " RESP
if [ "$RESP" == y ] || [ "$RESP" == Y ]; then
    rsync $ARGS --progress "$@"
fi

rm "$LOG" #< TODO: trap!
echo Done!

