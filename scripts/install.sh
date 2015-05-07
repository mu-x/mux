#!/bin/bash
#
# mux-install
#   Creates symlinks to all scripts but itself
#

set -e

LOCAL=${LOCAL:-/usr/local/bin}
PREFIX=${PREFIX:-mux-}

SELF=$(basename "${BASH_SOURCE[0]}")
HOME=/home/$SUDO_USER
cd "$(dirname "${BASH_SOURCE[0]}")"

echo Remove old "$LOCAL/$PREFIX*" ... done
for LINK in $(echo $LOCAL/$PREFIX*)
do
    unlink $LINK 2>/dev/null || true
done

for SCRIPT in $(echo *)
do
    chmod +x $SCRIPT
    LINK=$(echo $SCRIPT | cut -d. -f1)

    if [[ $SCRIPT != $SELF ]]
    then
        SYMLINK=$LOCAL/$PREFIX$LINK
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
    . ~/.muxrc
fi" >> $BASHRC

