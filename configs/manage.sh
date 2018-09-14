#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Manages configs in user's home directory and repository
Usage: $0 [status|push|pull|diff|merge]
END
exit 0; fi

set -e
[ $X ] && set -x

cd $(dirname "${BASH_SOURCE[0]}")
source "../scripts/resources/tools.sh"

function find_configs {
    if mux_is_windows; then
        find . -type f -not -name '*.sh'
    else
        find . -type f -name '.*' -and -not -name '*.sh'
    fi
}

function silent_diff {
    if [ "$3" == copy_none ] && [ ! -e "$2" ]; then
        cp "$1" "$2"
    else
        diff "$1" "$2" >/dev/null 2>&1
    fi
}

function merge {
    meld "$@" >/dev/null 2>&1
}

function each_rc {
    ACTION="$1"
    NAME=${2:-$ACTION}
    RETURN_CODE=0

    mkdir -p $HOME || true
    for FILE in $(find_configs); do
        LOCAL="$HOME/$FILE"
        REMOTE="$PWD/$FILE"

        echo ">   $NAME    for    $FILE"
        if ! eval $ACTION; then
            echo 'Different'
            RETURN_CODE=1
        fi
    done
    return $RETURN_CODE
}

for ARG in ${@:-status}; do
    case $ARG in
        save|push)
			each_rc 'cp "$LOCAL" "$REMOTE"' 'copy $LOCAL to $REMOTE'
			;;
        load|pull)
			each_rc 'cp "$REMOTE" "$LOCAL"' 'copy $REMOTE to $LOCAL'
			;;
        meld|merge)
			each_rc 'silent_diff "$LOCAL" "$REMOTE" || merge "$LOCAL" "$REMOTE"' \
                'merge $LOCAL to $REMOTE'
			;;
        diff)
			each_rc 'diff "$LOCAL" "$REMOTE"' ''
			;;
        sync)
            if ! each_rc 'silent_diff "$REMOTE" "$LOCAL" copy_none'; then
                read -p "Some configs are different, do we pull merge? " ACTION
                [ "$ACTION" ] && "./$(basename ${BASH_SOURCE[0]})" "$ACTION"
            fi
            ;;
        *)
            each_rc 'silent_diff "$LOCAL" "$REMOTE"' \
                'compare $REMOTE to $LOCAL'
            ;;
    esac
done

