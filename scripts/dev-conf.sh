#!/bin/bash
#
# mux: Configurates laptop devices
#
# Usage:
#   <script> [<PARAM>=<VALUE> ...]
#
# Params:
#   TP - touchpad (enabled/disabled)
#   VOL - audiom volume (%)
#

set -e

for PARAM in $@
do
    eval $PARAM
done

TOUCHPAD=${T:-${MUX_TOUCHPAD:-1}}
VOLUME=${V:-${MUX_VOLUME:-120}}

echo Touchpad, set enabled: $TOUCHPAD
xinput set-prop 12 "Device Enabled" $TOUCHPAD

echo Audio, set volume: $VOLUME%
pactl -- set-sink-volume 0 $VOLUME%

