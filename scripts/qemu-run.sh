#!/bin/bash
#
# [HDD=PATH] mux-qemu-run
#   Runs QEMU virtual machine
#

set -e

HDD=$PWD/${HDD:-$(echo *.qcow2 | cut -d' ' -f1)}
SYSTEM=qemu-system
DEFAULT="-cpu host -m 2G" # -net user -curses

for EXT in x86_64 x86
do
    if [[ "$HD" == *$EXT* ]]
    then
        SYSTEM=$SYSTEM-$EXT
        break
    fi
done

echo Running $SYSTEM ... $HD
$SYSTEM $DEFAULT "$HD" $@
