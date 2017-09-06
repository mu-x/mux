#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Unpacks files from known archive format to neighbour directory
Usage: $0 unpack ARCHIVE [-f]
END
exit 0; fi

set -e
[ "$X" ] && set -x

ARCHIVE=$(readlink -f "$1")
DIRECTORY=$(dirname "$ARCHIVE")
NAME=$(basename "$ARCHIVE")

EXTRACT="$DIRECTORY/${NAME:0:$(expr index "$NAME" .)-1}"
if [ -d "$EXTRACT" ]
then
    if [[ "$2" == *-f* ]]
    then
        rm -rf $EXTRACT
    else
        echo error: Directory "$EXTRACT" already exists, use -f to override
        exit 1
    fi
fi

mkdir -p $EXTRACT
case "$NAME" in
    *.tar.gz|*.tgz)   tar -zxvf $ARCHIVE -C $EXTRACT ;;
    *.tar.bz2|*.tbz2) tar -jxvf $ARCHIVE -C $EXTRACT ;;
    *.tar.xz|*.txz)   tar -Jxvf $ARCHIVE -C $EXTRACT ;;

    *.zip) unzip $ARCHIVE -d $EXTRACT ;;
    *.rar) cd $EXTRACT && unrur el $ARCHIVE ;;
esac

