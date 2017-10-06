#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Creates symlinks to all scripts but itself
Usage: [PARAM=VALUE ...] $0
Defaults:
    LOCAL   = /usr/local/bin
    PREFIX  = mux-
END
exit 0; fi
echo $HOME

set -e
[ $X ] && set -x

LOCAL=${LOCAL:-/usr/local/bin}
PREFIX=${PREFIX:-mux-}

SELF=$(basename "${BASH_SOURCE[0]}")
[ $SUDO_USER ] && HOME=/home/$SUDO_USER
cd "$(dirname "${BASH_SOURCE[0]}")"

if [ "$SUDO_USER" ]; then
    echo Remove old "$LOCAL/$PREFIX*" ... done
    for SYMLINK in $(echo $LOCAL/$PREFIX*)
    do
        unlink $SYMLINK 2>/dev/null || true
    done
fi

if [ -f $HOME/.bashrc ] || uname -a | grep -q MINGW; then
    BASHRC=$HOME/.bashrc
else
    BASHRC=$HOME/.bash_profile
fi

for SCRIPT in $(echo *); do
    if [[ $SCRIPT != $SELF && $SCRIPT != resources ]]; then
        chmod +x $SCRIPT
        LINK=$PREFIX$(echo $SCRIPT | cut -d. -f1)
        if [ "$SUDO_USER" ]; then
            SYMLINK=$LOCAL/$PREFIX$(echo $SCRIPT | cut -d. -f1)
            ln -sf $PWD/$SCRIPT $LOCAL/$LINK
        else
            [ ! "$(grep $PWD/$SCRIPT $BASHRC)" ] && \
                echo "alias $LINK=$PWD/$SCRIPT" >> $BASHRC
        fi
        echo Install $LINK ... done
    fi
done

if [ "$(grep .muxrc $BASHRC)" ]; then
    echo Update $BASHRC ... no need
    exit 0
fi

echo Update $BASHRC ... done
echo -e "
# MU eXecutables config
if [ -f ~/.muxrc ]
then
    export MUX_HOME=$(dirname $PWD)
    . ~/.muxrc
fi" >> $BASHRC

