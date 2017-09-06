#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Creates symlinks to all scripts but itself
Usage: [PARAM=VALUE ...] $0
Defaults:
    LOCAL   = /usr/local/bin
    PREFIX  = mux-
END
exit 0; fi

set -e

LOCAL=${LOCAL:-/usr/local/bin}
PREFIX=${PREFIX:-mux-}

SELF=$(basename "${BASH_SOURCE[0]}")
HOME=/home/$SUDO_USER
cd "$(dirname "${BASH_SOURCE[0]}")"

echo Remove old "$LOCAL/$PREFIX*" ... done
for SYMLINK in $(echo $LOCAL/$PREFIX*)
do
    unlink $SYMLINK 2>/dev/null || true
done

for SCRIPT in $(echo *)
do
    if [[ $SCRIPT != $SELF && $SCRIPT != resources ]]
    then
        chmod +x $SCRIPT
        SYMLINK=$LOCAL/$PREFIX$(echo $SCRIPT | cut -d. -f1)
        ln -sf $PWD/$SCRIPT $SYMLINK
        echo Install $SYMLINK ... done
    fi
done


if [ -f $HOME/.bashrc ]
then
    BASHRC=$HOME/.bashrc
else
    BASHRC=$HOME/.bash_profile
fi

if [ "$(grep .muxrc $BASHRC)" ]
then
    echo Update $BASHRC ... no need
    exit 0 # dont need an update
fi

echo Update $BASHRC ... done
echo -e "
# MU eXecutables config
if [ -f ~/.muxrc ]
then
    export MUX_HOME=$(dirname $PWD)
    . ~/.muxrc
fi" >> $BASHRC

