#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Download youtube audio into directory
Usage: [OPTION=VALUE ...] $0 URL
Options:
    V - version of youtube-dl (if not exist)
    L - local binary path
END
exit 0; fi

set -e
[ "$X" ] && set -x

URL=$1
VERSION=${V:-2016.06.16}
LOCAL=${L:-/usr/local/bin/youtube-dl}

if [[ ! $(which youtube-dl) ]]; then
    sudo wget https://yt-dl.org/downloads/$VERSION/youtube-dl -O $LOCAL
    sudo chmod a+rx $LOCAL
fi

OPTIONS="--extract-audio --audio-format mp3"
[[ $(which ffmpeg) ]] && OPTIONS+=" --prefer-ffmpeg"

set -x
youtube-dl $OPTIONS $URL

