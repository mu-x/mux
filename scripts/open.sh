#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Opens local or remote URLs by native applications.
Usage:
    [T=xdg-open] $0 ~/path/to/some/local/file.ext
    [T=nautilus] $0 '\\path\to\wondows\share'
END
exit 0; fi

set -e
[ "$X" ] && set -x

USER_URL="$1"
URL="$(echo "$USER_URL" | sed 's/\\/\//g')"
[[ "$USER_URL" =~ '\\'* ]] && URL="smb:$URL"

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

if [[ "$URL" =~ 'smb'* ]]; then
    OPEN=$(select_tool $SMB_TOOLS)
else
    OPEN=$(select_tool $OPEN_TOOLS)
fi

set -x
$OPEN "$URL" 1>/dev/null 2>&1 &

