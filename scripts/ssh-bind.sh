#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Creates alias for SSH host and uploads public key
Usage: [KEY=~/.ssh/key.pub] $0 USER PASSWORD HOST ALIAS
END
exit 0; fi

set -e -x

USER="$1"
PASSWORD="$2"
HOST="$3"
ALIAS="$4"
KEY=${KEY:-$MUX_SSH_KEY}

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

SSH_DIR="$HOME/.ssh"
mkdir -p "$SSH_DIR"

if [ ! "$KEY" ]; then
    KEY_BASE="$SSH_DIR/mux"
    if [ ! -f "$KEY_BASE" ]; then
        ssh-keygen -t rsa -N "" -f "$KEY_BASE"
        mux_use_ssh_keys "$KEY_BASE"
    fi
    KEY="$KEY_BASE.pub"
fi

RUN="sshpass -p $PASSWORD"
INFO="Connection '$USER:$PASSWORD@$HOST'"
$RUN ssh -o StrictHostKeyChecking=no "$USER@$HOST" echo $INFO works \
    || mux_fatal $INFO failed

if [ ! "$ALIAS" ]; then
    echo "Alias argument is required, see --help" >&2
    exit 1
fi

CONFIG="$SSH_DIR/config"
if grep "Host $ALIAS" "$CONFIG" >/dev/null 2>&1; then
    echo "WARNING: Alias '$ALIAS' already exists"
else
    cat >> "$CONFIG" <<END
Host $ALIAS
    HostName $HOST
    User $USER
    # Password $PASSWORD

END
fi

chmod 600 "$CONFIG"
INFO="Alias '$ALIAS'"
$RUN ssh "$ALIAS" echo "$INFO works" || mux_fail $INFO failed

if [ "$KEY" ]; then
    $RUN scp "$KEY" "$ALIAS:/tmp/ssh-key.pub"
    $RUN ssh $ALIAS 'mkdir -p .ssh; cat /tmp/ssh-key.pub >> .ssh/authorized_keys'
    ssh "$ALIAS" echo "Public key [ $KEY ] works"
fi

