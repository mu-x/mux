#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Creates
Usage: [KEY=~/.ssh/key.pub] $0 USER PASSWORD HOST ALIAS
END
exit 0; fi

set -e
[ "$X" ] && set -x

USER="$1"
PASSWORD="$2"
HOST="$3"
ALIAS="$4"
KEY=${KEY:-$MUX_SSH_KEY}

RUN="sshpass -p $PASSWORD"
$RUN ssh "$USER@$HOST" echo "Connection '$USER:$PASSWORD@$HOST' works" || exit 1

if [ ! "$ALIAS" ]; then
    echo "Alias argument is required, see --help" >&2
    exit 1
fi

if grep "Host $ALIAS" ~/.ssh/config >/dev/null 2>&1; then
    echo "WARNING: Alias '$ALIAS' already exists"
else
    cat >> ~/.ssh/config <<END
        Host $ALIAS
            HostName $HOST
            User $USER
            # Password $PASSWORD
END
fi
$RUN ssh "$ALIAS" echo "Alias '$ALIAS' works"

if [ "$KEY" ]; then
    $RUN scp "$KEY" "$ALIAS:/tmp/ssh-key.pub"
    $RUN ssh $ALIAS 'mkdir -p .ssh; cat /tmp/ssh-key.pub >> .ssh/authorized_keys'
    ssh "$ALIAS" echo Public key $KEY works
fi

