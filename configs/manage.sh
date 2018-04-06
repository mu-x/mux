#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Manages configs in user's home directory and repository
Usage: $0 [status|push|pull|diff|merge]
END
exit 0; fi

set -e
[ $X ] && set -x

cd $(dirname "${BASH_SOURCE[0]}")

CONFIG_FILES="$(find -type f -name '.*')"
if uname -a | grep -q MINGW; then
	CONFIG_FILES+=" $(find ./AppData -type f)"
fi

function silent_diff {
    diff "$@" >/dev/null 2>1
}

function each_rc {
    ACTION="$1"
    NAME=${2:-$ACTION}
    for FILE in $CONFIG_FILES; do
        LOCAL=$HOME/$FILE
        REMOTE=$PWD/$FILE
        echo $NAME for $FILE
        eval $ACTION || true
    done
}

for ARG in ${@:-status}; do
    case $ARG in
        save|push)
			each_rc 'cp $LOCAL $REMOTE' 'copy $LOCAL $REMOTE'
			;;
        load|pull)
			each_rc 'mkdir -p $(dirname $LOCAL) && cp $REMOTE $LOCAL' 'copy $REMOTE $LOCAL'
			;;
        meld|merge)
			each_rc 'silent_diff $LOCAL $REMOTE || meld $LOCAL $REMOTE'
			;;
        diff)
			each_rc 'diff $LOCAL $REMOTE'
			;;
        *)
			each_rc 'silent_diff $LOCAL $REMOTE || echo "---  Different"' 'diff $REMOTE $LOCAL'
			;;
    esac
done

echo Done
