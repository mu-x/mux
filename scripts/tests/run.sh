#!/bin/bash

set -e

ROOT_DIR=$(readlink -e "$(dirname "${BASH_SOURCE[0]}")"/..)
echo "ROOT_DIR=$ROOT_DIR"
source "$ROOT_DIR/resources/tools.sh"

cd /tmp
NO_ASK=1 mux_trace_run $ROOT_DIR/install.sh

for s in cdiff cmake dev-conf docker-run duplicates ffmpeg git-push grep \
    kill network nice open poormansprofiler port-forward python qemu-nbd \
    qemu-run qtcreator rbuild redirect rename repeat rsync signal ssh-bind \
    system-copy test-hdd ulimit vbox-mount vpn youtube-mp3
do
    mux_trace_run mux-$s -h
done

mux_title All tests passed

