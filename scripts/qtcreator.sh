#!/bin/bash
#
# mux: Runs Qt Creator for some dir in home
#
set -e

DIR=`echo ~/$1* | cut -d' ' -f1`
NAME=`basename $DIR`

function write_empty() {
    if [ ! -f $1 ]
    then
        echo $2 > $1
    fi
}

CUR_DIR="$PWD"
cd $DIR

write_empty $NAME.config "#define __GXX_EXPERIMENTAL_CXX0X__ 1"
write_empty $NAME.creator "[General]"
write_empty $NAME.includes "/usr/include /usr/local/include"
echo *.* */*.* */*/*.* */*/*/*.* */*/*/*/*.* | tr ' ' '\n' \
    > $NAME.files

echo Running Qt Creator for $NAME
qtcreator $NAME.creator >/dev/null 2>&1 &
cd "$CUR_DIR"

