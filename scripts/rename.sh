#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Replaces substring for all files in current directory.
Usage:
    [MV=mv] $0 SUBSTRING REPLACENEMT
END
exit 0; fi

set -e
[ "$X" ] && set -x

MV=${MV:-mv}

ROLLBACK=/tmp/mux-rename.rollback
echo '#!/bin/bash' > $ROLLBACK
chmod +x $ROLLBACK

for NAME in *; do
    RENAME=$(python -c "print('''$NAME'''.replace('''$1''', '''$2'''))")
    [[ "$NAME" == "$RENAME" ]] && continue

    echo Rename: $NAME
    echo --- to: $RENAME

    $MV "$NAME" "$RENAME"
    echo $MV \'"$RENAME"\' \'"$NAME"\' >> $ROLLBACK
done

echo echo Rolled back >> $ROLLBACK
echo Done, rollback: $ROLLBACK
