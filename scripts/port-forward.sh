#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Forwards local ports to remote ports for remapping, etc.
Usage: [P=tcp] mux-port-forwad LOCAL_IP REMOTE_IP PORT[-REMOTE_PORT][,OTHER_PORTS]
END
exit 0; fi

set -e
[ "$X" ] && set -x

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
        iptables -t nat -A POSTROUTING -j MASQUERADE
    done
done
