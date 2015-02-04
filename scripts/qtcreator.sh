#!/bin/bash
#
# mux: Runs Qt Creator for some dir in home
#

set -e

DIR=$(readlink -f ${1:-.})
NAME=$(basename $DIR)
CUR_DIR="$PWD"
cd $DIR

function write_empty() {
    if [ ! -f $1 ]
    then
        echo $2 > $1
    fi
}

function list_files() {
    if [ -d .git ]; then git ls-files && return 0; fi
    if [ -d .svn ]; then svn ls && return 0; fi
    if [ -d .cvs ]; then cvs ls && return 0; fi

    shopt -s globstar
    for FILE in echo **
    do
        if [ ! -d $FILE ]; then echo $FILE; fi
    done
}

echo Update project config creator includes and files
write_empty $NAME.config "#define __GXX_EXPERIMENTAL_CXX0X__ 1"
write_empty $NAME.creator "[General]"
write_empty $NAME.includes "/usr/include /usr/local/include"
list_files | grep -vxE "\..+" > $NAME.files

echo Running Qt Creator for $NAME
qtcreator $NAME.creator >/dev/null 2>&1 &
cd "$CUR_DIR"

