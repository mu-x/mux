#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Searches for duplicates by calculating MD5
Usage: MASK='*' $0 [print|remove]
END
exit 0; fi

set -e

declare -A FILE_HASHES
for FILE in ${MASK:-*}; do
    MD5=$(md5sum "$FILE")
    echo $MD5
    HASH=$(echo "$MD5" | awk '{print $1}')
    KNOWN_FILE="${FILE_HASHES[$HASH]}"
    if [ ! -z "$KNOWN_FILE" ]; then
        echo "$FILE" === "$KNOWN_FILE"
        [ "$1" == remove ] && rm "$FILE"
    fi
    FILE_HASHES[$HASH]="$FILE"
done
