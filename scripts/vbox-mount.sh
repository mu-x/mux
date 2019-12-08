#!/bin/bash
if [[ "$1" == --help ]] || [[ "$1" == -h ]] || [[ ! "$1" ]]; then cat <<END
Mounts Virtual Box share for current user.
Usage: $0 [SHARE_NAME or c] [MOUNT_PATH or /\$SHARE]
END
exit 0; fi

set -e
[ $X ] && set -x

SHARE_NAME=${1:c}
MOUNT_PATH=${2:-/$(echo $SHARE_NAME | tr '[:upper:]' '[:lower:]')}
echo "Mount $SHARE_NAME to $MOUNT_PATH"

sudo mkdir -p "$MOUNT_PATH"
sudo chown "$USER:$USER" "$MOUNT_PATH"
sudo mount -t vboxsf -o uid=$UID "$SHARE_NAME" "$MOUNT_PATH"
