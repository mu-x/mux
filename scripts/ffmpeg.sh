#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Converts video files by FFMPEG or libAV.
Usage: [OPTION=VALUE ...] $0 [VIDEO FILES ...]
Options:
    Q   Quality 1..31, default is 1 (the best)
    D   Output directory, default is $PWD
    C   Container, default mp4
    VC  AV video codec, default is h264
    AC  AV auudio codec, default is just copy
END
exit 0; fi

set -e
[ "$X" ] && set -x

QUALITY=${Q:-1}
DIRECTORY=${D:-.}
CONTAINER=${C:-mp4}
VIDEO_CODEC=${VC:-libx264}
AUDIO_CODEC=${AC:-copy}

PROBE=${MUX_FFMPEG_PROBE:-avprobe}
CONVERT=${MUX_FFMPEG_CONVERT:-avconv}

function pure_file_name() {
    local name=$(basename "$1")
    python -c "print('.'.join('$name'.split('.')[:-1]))"
}

for SOURCE in "$@"; do
    TARGET="$DIRECTORY"/$(pure_file_name "$SOURCE").$CONTAINER
    echo "<<<<<<< $SOURCE"
    echo ">>>>>>> $TARGET"
    $CONVERT -i "$SOURCE" -qscale $QUALITY -c:v $VIDEO_CODEC -c:a $AUDIO_CODEC "$TARGET"
done
echo Done
