#!/bin/bash
#
# mux: Mounts qcow2 HHD image over NBD
#

set -e
modprobe nbd

HD=$PWD/${HD:-`echo *.qcow2 | cut -d' ' -f1`}
NBD=/dev/${NBD:-nbd7}

case ${1-help} in
c|connect)
    echo Connect $HD to $NBD
    qemu-nbd -c $NBD $HD

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
    echo "Usage: [HD=*.qcow] [NBD=nbd7] $0 [connect|disconnect]"

esac

