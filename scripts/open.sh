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
source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

USER_URL="$1"
shift

if mux_is_windows; then
    URL="$USER_URL"

    if [ "$(file "$URL" | grep text)" ]; then
        TOOLS="notepad++ notepad"
    else
        TOOLS="start"
    fi
else
    URL="$(echo "$USER_URL" | sed 's/\\/\//g')"
    [[ "$USER_URL" =~ '\\'* ]] && URL="smb:$URL"

    if [[ "$URL" =~ 'smb'* ]]; then
        TOOLS="konqueror nautilus"
    else
        TOOLS="xdg-open kde-open open"
    fi
fi

mux_first_gui_tool "$T $TOOLS" "$URL" "$@"

