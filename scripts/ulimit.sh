#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Cunfigure system limits for GNU/Linux.
Usage: $0 [nofile] [nproc] [core]
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ $X ] && set -x

if [ $(whoami) != root ]; then
    sudo X=$X $0 "$@"
    exit $?
fi

NOFILE=${1:-65535}
NPROC=${2:-65535}
CORE=${3:-unlimited}

echo "--- /etc/security/limits.conf"
mux_replace_in_file /etc/security/limits.conf '* - nofile '$NOFILE
mux_replace_in_file /etc/security/limits.conf '* - nproc '$NPROC
mux_replace_in_file /etc/security/limits.conf '* - core '$CORE

if [ -d /etc/systemd ]; then
    for file in /etc/systemd/system.conf /etc/systemd/user.conf; do
        echo "--- $file"
        mux_replace_in_file "$file" "DefaultLimitNOFILE=" "$NOFILE"
        mux_replace_in_file "$file" "DefaultLimitNPROC=" "$NPROC"
        mux_replace_in_file "$file" "DefaultLimitCORE=" "$CORE"
    done
fi

echo "---"
if [ "$MUX_IS_REPLACED" ]; then
    mux_confirm "Reboot is required, do it now?" && reboot
else
    echo Reboot is not required.
fi

