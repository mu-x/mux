#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Manages configs in user's home directory and repository
Usage: $0 [status|push|pull|merge]
END
exit 0; fi

set -e
[ $X ] && set -x

cd $(dirname "${BASH_SOURCE[0]}")

CONFIG_FILES="$(find -type f -name '.*')"
if uname -a | grep -q MINGW; then
	CONFIG_FILES+=" $(find ./AppData -type f)"
fi

function each_rc {
    ACTION="$1"
    for FILE in $CONFIG_FILES; do
        LOCAL=$HOME/$FILE
        REMOTE=$PWD/$FILE
        echo $ACTION for $FILE
        eval $ACTION || true
    done
}

for ARG in ${@:-status}; do
    case $ARG in
        save|push)  
			each_rc 'cp $LOCAL $REMOTE'                             	
			;;
        load|pull)  
			each_rc 'mkdir -p $(dirname $LOCAL) && cp $REMOTE $LOCAL'	
			;;
        meld|merge) 
			each_rc 'diff $LOCAL $REMOTE || meld $LOCAL $REMOTE'    	
			;;
        *)          
			each_rc 'diff $LOCAL $REMOTE'                           	
			;;
    esac
done

echo Done
