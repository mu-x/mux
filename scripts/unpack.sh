#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Unpacks files from known archive format to neighbour directory
Usage: $0 ARCHIVE [-f]
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ "$X" ] && set -x

ARCHIVE="$1"
DIRECTORY=$(dirname "$ARCHIVE")
NAME=$(basename "$ARCHIVE")

EXTRACT="$DIRECTORY/${NAME:0:$(expr index "$NAME" .)-1}"
if [ -d "$EXTRACT" ]; then
    if [[ "$2" == *-f* ]]; then
        mux_trace_run rm -rf "$EXTRACT"
    else
        mux_fail Directory "$EXTRACT" already exists, use -f to override
    fi
fi

mkdir -p $EXTRACT
case "$NAME" in
    *.tar.*|*.t*z*) mux_trace_run tar -xvf "$ARCHIVE" -C "$EXTRACT" ;;
    *.zip) mux_trace_run unzip "$ARCHIVE" -d "$EXTRACT" ;;
    *) mux_trace_run 7z x "$ARCHIVE" -bb3 -o"$EXTRACT" ;;
esac

