#!/bin/bash
#
# mux: Runs docker container, mounts current directory inside
#

set -e ### Preconfig

# If stdout is not a terminal, send Ctrl+D to stdin and redirect stderr to
# stdout (to prevent docker to be waiting on stdin)
if [ -t 1 ]
then
    PRE=; POST=;
else
    if [ ! -t 0 ]; then PRE='echo |'; fi
    if [ ! -t 2 ]; then POST='2>&1'; fi
fi

# Transfer home cache if container user is specified
CUSER=${CU:-${MUX_DOCKER_CUSER:-}}
CMOUNTS=".ivy .cache .m $CM"
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


set -x ### Docker Run

IMAGE=${IMG:-${MUX_DOCKER_IMAGE:-ubuntu}}
COMMAND=${@:-${MUX_DOCKER_COMMAND:-bash}}

$PRE docker run $MOUNTS -v $PWD:/code -it $IMAGE \
        bash -c "cd /code && $COMMAND" $POST
