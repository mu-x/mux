#!/bin/bash
if [[ "$1" == --help ]] || [[ "$1" == -h ]] || [[ ! "$1" ]]; then cat <<END
Finds processes by grep and offers to kill them.
Usage: [PS="ps aux"] $0 PROCCESS_MASK
END
exit 0; fi

set -e
[ $X ] && set -x

NAME=$1
PS=${PS:-"ps aux"}

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

LIST=$($PS | grep -v ' grep ' | grep "$NAME")
# TODO: Print some message if process is not found.

$PS | head -1
echo "$LIST"
echo
read -p 'Select PIDs, blank for everyone: ' PIDS

if [ ! "$PIDS" ]; then
    if mux_is_windows; then
        PIDS=$(echo "$LIST" | awk '{print$1}')
    else
        PIDS=$(echo "$LIST" | awk '{print$2}')
    fi
fi

for PID in $PIDS; do
    echo Killing PID $PID
    kill -9 $PID
done

