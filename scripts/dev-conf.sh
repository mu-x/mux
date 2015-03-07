#!/bin/bash
#
# mux-dev-conf [<PARAM>=<VALUE> ...]
#   Configurates laptop devices
#
# Params:
#   T - touchpad (enabled/disabled), default=1
#   V - audiom volume (%), default=120
#

set -e

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

