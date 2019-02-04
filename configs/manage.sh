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
        find . -type f -not -name '*.sh*' | grep -v .config
    else
        find -L . -type f -not -name '*.sh*' | grep -v AppData
    fi
}

function check_files {
    for FILE in "$@"; do
        if [ ! -f "$FILE" ]; then
            echo "'$FILE' does not exist"
            return 1
        fi
    done
}

function copy {
    mkdir -p "$(dirname "$2")"
    cp "$1" "$2"
}

function silent_diff {
    if [ "$3" == copy_none ] && [ ! -f "$2" ]; then
        copy "$1" "$2"
    else
        check_files "$1" "$2" || true
        diff "$1" "$2" >/dev/null 2>&1
    fi
}

function merge {
    check_files "$@" || true
    meld "$@" >/dev/null 2>&1
}

function each_rc {
    ACTION="$1"
    NAME="${2:-$ACTION}"
    RETURN_CODE=0

    find_configs | while IFS= read -r FILE; do
        LOCAL="$HOME/$FILE"
        REMOTE="$PWD/$FILE"

        echo "> $NAME for '$FILE'"
        if ! eval "$ACTION"; then
            echo 'different'
            RETURN_CODE=1
        fi
    done
    return $RETURN_CODE
}

for ARG in ${@:-status}; do
    case $ARG in
        save|push)
			each_rc 'copy "$LOCAL" "$REMOTE"' 'copy $LOCAL to $REMOTE'
			;;
        load|pull)
			each_rc 'copy "$REMOTE" "$LOCAL"' 'copy $REMOTE to $LOCAL'
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

