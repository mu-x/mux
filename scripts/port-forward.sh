#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Forwards local ports to remote ports for remapping, etc.
Create:
    [P=tcp] $0 LOCAL_IP REMOTE_IP PORT[-REMOTE_PORT][,OTHER_PORTS]
List/Delete All:
    $0 list|delete
END
exit 0; fi

set -e
[ "$X" ] && set -x

if [ $(whoami) != root ]; then
    sudo $0 "$@"
    exit $?
fi

if [ "$1" == list ]; then
    iptables -t nat --line-numbers -L
    exit $?
fi

if [ "$1" == delete ]; then
    COUNT=0
    while iptables -t nat -D PREROUTING 1; do ((COUNT++)) || true; done
    while iptables -t nat -D POSTROUTING 1; do :; done
    echo Removed $COUNT rules.
    exit 0
fi

PROTOCOLS=${P:-tcp udp}
if [ ! "$1" ] || [ ! "$2" ] || [ ! "$3" ]; then
    echo "Error: Wrong usage, try --help" >&2
    exit 1;
fi

LOCAL_IP=$1
REMOTE_IP=$2
IFS=',' read -ra PORTS <<< "$3"

sysctl net.ipv4.ip_forward=1
for PORT in "${PORTS[@]}"; do
    IFS='-' read -ra PORT_PARTS <<< "$PORT"
    LOCAL_PORT=${PORT_PARTS[0]}
    REMOTE_PORT=${PORT_PARTS[1]:-$LOCAL_PORT}

    echo "Forward $LOCAL_IP:$LOCAL_PORT to $REMOTE_IP:$REMOTE_PORT for $PROTOCOLS"
    for PROTO in $PROTOCOLS; do
        iptables -t nat -A PREROUTING -p $PROTO -d $LOCAL_IP --dport $LOCAL_PORT \
            -j DNAT --to-destination $REMOTE_IP:$REMOTE_PORT
    done
done
iptables -t nat -A POSTROUTING -j MASQUERADE
