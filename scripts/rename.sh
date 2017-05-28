#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Replaces substring for all files in current directory.
Usage:
    mux-rename SUBSTRING REPLACENEMT
END
exit 0; fi

set -e
[ "$X" ] && set -x

ROLLBACK=/tmp/mux-rename.rollback
echo '#!/bin/bash' > $ROLLBACK
chmod +x $ROLLBACK

for NAME in ./*; do
    NEW_NAME="${NAME/$1/$2}"
    [[ "$NAME" == "$NEW_NAME" ]] && continue

    echo Rename \'$NAME\' to \'$NEW_NAME\'
    mv "$NAME" "$NEW_NAME"
    echo mv \'"$NEW_NAME"\' \'"$NAME"\' >> $ROLLBACK
done

echo echo Rolled back >> $ROLLBACK
echo Done, rollback: $ROLLBACK
