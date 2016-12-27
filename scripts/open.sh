#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Opens local or remote URLs by native applications.
Usage:
    [T=xdg-open] mux-open ~/path/to/some/local/file.ext
    [T=nautilus] mux-open '\\\\path\to\wondows\share'
END
exit 0; fi

set -e
[ "$X" ] && set -x

USER_URL="$1"
URL=$(echo -e "$USER_URL" | sed 's/\\/\//g')

SMB_TOOLS="$T konqueror nautilus"
OPEN_TOOLS="$T xdg-open kde-open"

function select_tool()
{
    for tool in $@; do
        which $tool && return 0
    done

    echo No such tools: $@ >&2
    exit 1
}

if [[ "$USER_URL" =~ '\\'* ]]; then
    URL="smb:/$URL"
    OPEN=$(select_tool $SMB_TOOLS)
else
    OPEN=$(select_tool $OPEN_TOOLS)
fi

set -x
$OPEN "$URL" 1>/dev/null 2>&1 &

