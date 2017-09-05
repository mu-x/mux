#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Copies corrently running system into new HDD
Usage: [NO_GRUB=1] $0 HDD_DEVICE
END
exit 0; fi

set -e
[ "$X" ] && set -x

DEVICE=$1
if [ -z "$DEVICE" ]; then
    echo 'Error: device argument is required.' >&2
    exit 1
fi

mkdir -p $MOUNT
umount $DEVICE || true
mount $DEVICE $MOUNT

# Copy entire root partition with preserved permisions
rsync -ax --progress / $MOUNT

if [ -z $NO_GRUB ]; then
    for DIR in sys proc dev; do
        mount -o bind /$DIR $MOUNT/$DIR
    done

    chroot $MOUNT
    blkid
    grub-install $MOUNT
    update-grub
fi

umount $MOUNT
rmdir $MOUNT

