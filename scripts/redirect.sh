#!/bin/bash
#
# mux-redirect EXECUTABLE [STDOUT] [STDERR]
#   Redirects running process stdout and stderr
#

set -e

TARGET=$1
if [ ! "$TARGET" ]
then
    echo "Usage: <script> executable|pid [stdout] [stderr]"
    exit 1
fi

if [[ $TARGET =~ ^-?[0-9]+$ ]]
then
    PID=$TARGET
    EXE=$(ps --pid=$PID -o cmd | tail -1 | awk '{print$1}')
else
    PID=$(pgrep $TARGET | head -1)
    EXE=$TARGET
fi

OUT=${2:-/dev/null}
[ ! -f $OUT ] && touch $OUT

ERR=${3:-$OUT}
[ ! -f $ERR ] && touch $ERR

REDIR="stdout to $OUT, stderr to $ERR"

if [ ! "$PID" ]
then
    echo Process does not exist, start $EXE with $REDIR
    $EXE >$OUT 2>$ERR &

    echo Done!
    exit 0
fi

echo Redirecting $EXE $PID $REDIR
gdb $EXE $PID >/dev/null 2>&1 <<EOF
    p close(1)
    p open("$OUT", 0600)

    p close(2)
    p open("$ERR", 0600)

    detach
    quit
EOF

echo Done!
