#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Manages configs in user's home directory and repository
Usage: $0 [status|push|pull]
END
exit 0; fi

set -e
[ $X ] && set -x

cd $(dirname "${BASH_SOURCE[0]}")

function each_rc {
    ACTION="$1"
    for CONF in $(echo .??*); do
        LOCAL=$HOME/$CONF
        REMOTE=$PWD/$CONF
        echo $ACTION for $CONF
        eval $ACTION || true
    done
}

for ARG in ${@:-status}; do
    case $ARG in
        save|push)  each_rc 'cp $LOCAL $REMOTE'             ;;
        load|pull)  each_rc 'cp $REMOTE $LOCAL'             ;;
        *)          each_rc 'diff $LOCAL $REMOTE'           ;;
    esac
done

echo Done
