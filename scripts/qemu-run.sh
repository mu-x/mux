#!/bin/bash
#
# mux: Runs QEMU virtual machine
#
set -e -x

HD=$PWD/${HD:-`echo *.qcow2 | cut -d' ' -f1`}
SYSTEM=qemu-system
DEFAULT="-cpu host -net user -m 2G" # -curses"

for EXT in x86_64 x86
do
    if [[ "$HD" == *$EXT* ]]
    then
        SYSTEM=$SYSTEM-$EXT
        break
    fi
done

# Run qemu-system-XXX
$SYSTEM $DEFAULT "$HD" $@
