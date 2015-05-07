#!/bin/bash
#
# mux-redirect EXECUTABLE [STDOUT] [STDERR]
#   Redirects running process stdout and stderr
#

set -e

EXE=$1
if [ ! "$EXE" ]
then
    echo "Usage: <script> executable [stdout] [stderr]"
    exit 1
fi

OUT=${2:-/dev/null}
[ ! -f $OUT ] && touch $OUT

ERR=${3:-$OUT}
[ ! -f $ERR ] && touch $ERR

REDIR="stdout to $OUT, stderr to $ERR"

PID=$(pgrep $EXE | head -1)
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
