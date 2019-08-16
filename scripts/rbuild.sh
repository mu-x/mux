#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Brings a local patch to the remote machine and builds it there.
Usage:
    $0 host dir command [command_options]
Example:
    $0 user@builder ~/project ./build.sh --debug
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ ! $K ] && clear
[ "$X" ] && set -x

HOST=$1; shift
DIR=$1; shift
PATCH="/tmp/mux-rbuild-$(date +%s).patch"

if [ -d .git ]; then
    BASE=$(git rev-parse HEAD)
    git diff HEAD >$PATCH
    ssh $HOST bash -i <<END
        cd $DIR
        git checkout -f $BASE"
END
elif [ -d .hg ]; then
    BASE=$(hg id -i | tr '+' ' ')
    hg diff >$PATCH
    ssh $HOST bash -i <<END
        cd $DIR
        hg update -C $BASE
END
else
    mux_fail You have to be in the root of VSC
fi

scp $PATCH $HOST:$PATCH
ssh $HOST bash -i <<END
    export TERM=$TERM
    source ~/.bashrc
    cd $DIR
    patch -p1 <$PATCH
    $@
END
