#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Configurates laptop devices
Usage: $0 [<PARAM>=<VALUE> ...]
Params:
    T - touchpad (enabled/disabled), default=1
    V - audio volume (%), default=120
END
exit 0; fi

set -e
[ "$X" ] && set -x

for PARAM in $@
do
    eval $PARAM
done

TOUCHPAD=${T:-${TP:-${TOUCHPAD:-${MUX_TOUCHPAD:-1}}}}
VOLUME=${V:-${VOL:-${VOLUME:-${MUX_VOLUME:-120}}}}

echo Touchpad, set enabled: $TOUCHPAD
xinput set-prop 12 "Device Enabled" $TOUCHPAD

echo Audio, set volume: $VOLUME%
pactl -- set-sink-volume 0 $VOLUME%

