#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Mounts qcow2 HHD image over NBD
Usage: [HDD=PATH] [NBD=nbdX] mux-qemu-nbd [c|connect|d|disconnect]
END
exit 0; fi

set -e
modprobe nbd

HDD=$PWD/${HDD:-`echo *.qcow2 | cut -d' ' -f1`}
NBD=/dev/${NBD:-nbd7}

case ${1:-error} in
c|connect)
    echo Connect $HDD to $NBD
    qemu-nbd -c $NBD $HDD

    for PT in ${NBD}p*
    do
        DIR=$PWD/`basename $PT`
        mkdir -p -m 777 $DIR
        if ! mount -v $PT $DIR
        then
            rm -rf $DIR
        fi
    done
    ;;

d|disconnect)
    for PT in ${NBD}p*
    do
        DIR=$PWD/`basename $PT`
        umount $DIR || true
        rm -rf $DIR || true
    done
    qemu-nbd -d $NBD
    ;;

*)
    echo Error usage, use --help for more info >&2
    exit 1
    ;;

esac

