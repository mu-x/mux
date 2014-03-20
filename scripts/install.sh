#!/bin/bash
#
# mux: Creates symlinks to all scripts but itself
#
set -e

LOCAL=/usr/local/bin
PREFIX=mux-

SELF=$(basename "${BASH_SOURCE[0]}")
cd "$(dirname "${BASH_SOURCE[0]}")"

for SCRIPT in `echo *`
do
    chmod +x $SCRIPT
    LINK=$(echo $SCRIPT | cut -d. -f1)

    if [[ $SCRIPT != $SELF ]]
    then
        ln -sf $PWD/$SCRIPT $LOCAL/$PREFIX$LINK
        echo install $SCRIPT ... done
    fi
done

