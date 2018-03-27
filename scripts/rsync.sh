#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Rsync helper with preview and some other features.
Usage: [NO_DELETE=1] [NO_LOG=1] $0 SOURCE TARGET
END
exit 0; fi

set -e
[ "$X" ] && set -x

ARGS="--archive"
[ -z "$NO_DELETE" ] && ARGS+=" --delete"

if [ ! "$NO_LOG" ]; then
    LOG=/tmp/mux-rsync-$(date +%s)
    echo Log file: "$LOG"
    rsync $ARGS --verbose --dry-run --stats "$@" > "$LOG"

    less "$LOG"
    IFS= read -p "Continue? (y/n): " RESP
else
    RESP=y
fi

if [ "$RESP" == y ] || [ "$RESP" == Y ]; then
    rsync $ARGS --progress "$@"
fi

[ ! $NO_LOG ] && rm "$LOG" #< TODO: trap!
echo Done!

