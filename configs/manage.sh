#!/bin/bash

cd $(dirname "${BASH_SOURCE[0]}")

function each_rc {
    ACTION="$1"
    for CONF in $(ls .*rc *.conf .*.conf)
    do
        LOCAL=$HOME/$CONF
        REMOTE=$PWD/$CONF
        echo $ACTION for $CONF
        eval $ACTION
    done
}

for ARG in ${@:-status}
do
    case $ARG in
        -h|*help)   echo "<script> [help|status|push|pull]" ;;
        save|push)  each_rc 'cp $LOCAL $REMOTE'             ;;
        load|pull)  each_rc 'cp $REMOTE $LOCAL'             ;;
        *)          each_rc 'diff $LOCAL $REMOTE'           ;;
    esac
done

echo Done
