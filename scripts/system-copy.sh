#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Copies corrently running system into new HDD
Usage: [NO_COPY=1] [GRUB=/dev/sda] $0 DEVICE_OR_DIRECTORY
END
exit 0; fi

set -e
[ "$X" ] && set -x

: ${1?"Error: you must specify device or mount point."}
if file "$1" | grep directory; then
    # Directory means mount point
    MOUNT="$1"
else
    MOUNT=/tmp/hdd_$(date +%s)
    mkdir -p "$MOUNT"

    # Otherwise it is supposed to be a block device
    DEVICE="$1"
    [ -z $NO_COPY ] && mkfs.ext4 "$DEVICE"
    mount "$DEVICE" "$MOUNT"
fi

# Copy entire root partition with preserved permisions
if [ -z $NO_COPY ]; then
    rsync -ax --progress / "$MOUNT"
fi

# Install boot loader
if [ "$GRUB" ]; then
    for DIR in sys proc dev; do
        mount -o bind "/$DIR" "$MOUNT/$DIR"
    done

    chroot "$MOUNT" <<EOF
        set -e
        blkid
        grub-install "$GRUB"
        update-grub
EOF

    for DIR in sys proc dev; do
        umount "$MOUNT/$DIR"
    done

    echo Do not forget to edit "$MOUNT/etc/fstab"
fi

# Unmount device if it was mounted
if [ $DEVICE ]; then
    umount $DEVICE
    rmdir $MOUNT
fi

