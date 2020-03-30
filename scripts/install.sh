#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Creates symlinks to all scripts but itself
Usage: [PARAM=VALUE ...] $0
Defaults:
    LOCAL   = /usr/local/bin
    PREFIX  = mux-
    NO_ASK  =
END
exit 0; fi

set -e
[ $X ] && set -x

LOCAL=${LOCAL:-/usr/local/bin}
PREFIX=${PREFIX:-mux-}

SELF=$(basename "${BASH_SOURCE[0]}")
cd "$(dirname "${BASH_SOURCE[0]}")"
source "resources/tools.sh"

if [ $SUDO_USER ]; then
    if mux_is_osx; then
        HOME=/Users/$SUDO_USER
    else
        HOME=/home/$SUDO_USER
    fi
fi

if [ $(whoami) == "root" ]; then
    mkdir -p "$LOCAL"
    echo Remove old "$LOCAL/$PREFIX*" ... done
    for SYMLINK in $(echo $LOCAL/$PREFIX*)
    do
        unlink $SYMLINK 2>/dev/null || true
    done
fi

BASHRC=$HOME/.bashrc
if [ ! -f $BASHRC ]; then
    [ $SUDO_USER ] && sudo -u $SUDO_USER touch $BASHRC
    echo "# Generated by mux" > $BASHRC
    echo "source $BASHRC" >> $HOME/.bash_profile
else
    [ "$(tail -1 $BASHRC)" != "" ] && echo >> $BASHRC
fi

for SCRIPT in $(echo *); do
    if [[ $SCRIPT != $SELF ]] && [[ -f $SCRIPT ]]; then
        chmod +x $SCRIPT
        LINK=$PREFIX$(echo $SCRIPT | cut -d. -f1)
        if [ $(whoami) == root ]; then
            SYMLINK=$LOCAL/$PREFIX$(echo $SCRIPT | cut -d. -f1)
            ln -sf $PWD/$SCRIPT $LOCAL/$LINK
        else
            if [ ! "$(grep $PWD/$SCRIPT $BASHRC)" ]; then
                echo "alias $LINK=$PWD/$SCRIPT" >> $BASHRC
            fi
        fi
        echo Install $LINK ... done
    fi
done

if [ "$(grep MUX_SSH_KEY $BASHRC)" ] || [ "$NO_ASK" ]; then
    echo Select SSH Key ... no need
else
    read -p "Select SSH Key (empty for auto generate): " SSH_KEY
    if [ "$SSH_KEY" ]; then
        SSH_KEY=$(eval "echo $SSH_KEY")
        [[ $SSH_KEY != *.pub ]] && SSH_KEY+=.pub
        [ ! -f $SSH_KEY ] && mux_fail $SSH_KEY does not exist
    else
        mkdir -p ~/.ssh
        SSH_KEY=~/.ssh/mux.pub
        ssh-keygen -t rsa -f ~/.ssh/mux || true
        [ "$SUDO_USER" ] && chown $SUDO_USER:$SUDO_USER -R ~/.ssh
    fi
    echo "export MUX_SSH_KEY=$SSH_KEY" >> $BASHRC
    echo Select SSH Key $SSH_KEY ... done
fi

if [ "$(grep .muxrc $BASHRC)" ]; then
    echo Update $BASHRC ... no need
else
    echo -e "if [ -f ~/.muxrc ]
then
    export MUX_HOME=$(dirname $PWD)
    . ~/.muxrc
fi
" >> $BASHRC
    echo Update $BASHRC ... done
fi

