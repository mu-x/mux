#!/bin/bash
#
# mux-install
#   Creates symlinks to all scripts but itself
#

set -e

LOCAL=${LOCAL:-/usr/local/bin}
PREFIX=${PREFIX:-mux-}

SELF=$(basename "${BASH_SOURCE[0]}")
cd "$(dirname "${BASH_SOURCE[0]}")"

MUXRC=/home/$SUDO_USER/.muxrc
BASHRC=/home/$SUDO_USER/.bashrc

for SCRIPT in `echo *`
do
    chmod +x $SCRIPT
    LINK=$(echo $SCRIPT | cut -d. -f1)

    if [[ $SCRIPT != $SELF ]]
    then
        ln -sf $PWD/$SCRIPT $LOCAL/$PREFIX$LINK
        echo Install $SCRIPT ... done
    fi
done

if [ ! -f $MUXRC ]
then
    echo MUX=true > $MUXRC
    echo . .muxrc >> $BASHRC
fi

