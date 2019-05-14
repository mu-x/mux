#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Crossplatform network utility.
Usage:
    $0 [COMMAND [ARGUMENTS]]
Commands:
    <empty>, i, ips     All ip addresses by inteface.
    l, listen [EXE]     TCP listening addresses.
    u, udp [EXE]        UDP receiving addresses.
END
exit 0; fi

set -e
[ "$X" ] && set -x

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

if mux_is_windows; then
    case ${1:-ips} in
        i|ips)      ipconfig | grep 'Ethernet\|IPv'                 ;;
        l|listen)   timeout 1 netstat -abp TCP | grep "\[$2" -B1    ;;
        u|udp)      netstat -abp UDP | grep "\[$2" -B1              ;;
        *)          mux_fail "Unknown command '$1', use --help"    ;;
    esac
else
    case ${1:-ips} in
        i|ips)      ifconfig | grep inet -B1                                ;;
        l|listen)   netstat -lpn | grep -E "tcp.+LISTEN" | grep ${2:-.+}    ;;
        u|udp)      netstat -lpn | grep udp | grep ${2:-.+}                 ;;
        *)          mux_fail "Unknown command '$1', use --help"            ;;
    esac
fi
