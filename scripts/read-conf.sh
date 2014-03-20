#!/bin/bash
#
# mux: Reads or created empty config file
#
set -e -x

CONFIG=$(echo ~)/.mux

if [ -f $CONFIG ]
then
    . $CONFIG
else
    echo "MUX=true" > "$CONFIG"
fi

