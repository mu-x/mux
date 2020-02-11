#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Starts openvpn in background and restarts if required
Usage:
    D="~/.openvpn" C="config_name" CH="ya.ru" $0
END
exit 0; fi

set -e
[ "$X" ] && set -x
source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

DIR=${D:-"$HOME/.openvpn"}
CONFIGS=*$C*.ovpn
CONTROL_HOST=${CH:-ya.ru}

[ $(whoami) != root ] && mux_fail Root permissions are required
cd $DIR
IFS=', ' read -r -a CONFIGS <<< $(echo $CONFIGS)
[ "${#CONFIGS[@]}" == 0 ] && mux_fail No configs in $DIR

if [ "${#CONFIGS[@]}" == 1 ]; then
    CONFIG=${CONFIGS[0]}
else
    for (( i = 0; i < ${#CONFIGS[@]}; i++ )); do echo "$i: ${CONFIGS[$i]}"; done
    read -p "Select config: " i
    CONFIG=${CONFIGS[i]}
fi

[ ! $CONFIG ] && mux_fail Config is not selected
[ ! -f $CONFIG ] && mux_fail Config does not exist $PWD/$CONFIG
while true; do
    mux_trace_run openvpn $CONFIG &
    sleep 1
    function onCtrlC {
        mux_trace_run pkill -KILL openvpn
        sleep 1 #< TODO: Wait for process exit the other way.
        exit 0
    }
    trap onCtrlC SIGINT
    while pgrep openvpn >/dev/null; do
        if [[ $(ping -c 2 -q -W 2 $CONTROL_HOST | grep transm | awk '{print $4}') == 0 ]]; then
            mux_trace_run pkill -KILL openvpn
            break
        fi
    done
done


