#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Runs docker container, mounts current directory inside
Usage: [I=IMAGE] [CU=USER] mux-docker-run [COMMAND]
Defaults:
    IMAGE=ubuntu, USER=builder, COMMAND=bash
END
exit 0; fi

set -e
[ "$X" ] && set -x

IMAGE=${I:-${IMG:-${MUX_DOCKER_IMAGE:-ubuntu}}}
COMMAND=${@:-${MUX_DOCKER_COMMAND:-bash}}
CUSER=${CU:-${MUX_DOCKER_CUSER:-}}
CMOUNTS=".ivy .cache .m $CM"

# Forward terminal to container and redirect std in otherwise
if [ -t 1 ]
then
    FLAGS=-it
    TAIL=

    # Reattach tty for screen inside container support
    # https://github.com/docker/docker/issues/728
    PRECONF="exec >/dev/tty 2>/dev/tty </dev/tty"
else
    FLAGS=-i
    TAIL=" 2>&1"
    PRECONF=
fi

# Transfer home cache if container user is specified
if [ $CUSER ]
then
    for LOCAL in $HOME/.*
    do
        NAME=$(basename "$LOCAL")
        if [[ "$CMOUNTS" == *"$NAME"* ]]
        then
            REMOTE="/home/$CUSER/$NAME"
            MOUNTS="$MOUNTS -v $LOCAL:$REMOTE"
        fi
    done
fi

# Run
set -x
docker run $FLAGS $MOUNTS -v $PWD:/code $IMAGE \
    bash -c "cd /code && $PRECONF && $COMMAND$TAIL"
