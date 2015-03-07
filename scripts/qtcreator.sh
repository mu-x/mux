#!/bin/bash
#
# [NOVC=1] [NOUPDATE=1] mux-qtcreator [PROJECT_DIRECTORY]
#   Runs Qt Creator for some dir in home
#

set -e

DIR=$(readlink -f ${1:-.})
NAME=$(basename $DIR)
CUR_DIR="$PWD"
cd $DIR


# HELPERS

function write_empty() {
    FILE=$1
    shift

    if [ ! -f $FILE ]
    then
        echo - create: $FILE
        echo $1 > $FILE
        shift

        while (( "$#" ))
        do
            echo $1 >> $FILE
            shift
        done
    fi
}

function list_files() {
    if [ ! "$NOVC" ]
    then
        if [ -d .git ]; then git ls-files && return 0; fi
        if [ -d .svn ]; then svn ls && return 0; fi
        if [ -d .cvs ]; then cvs ls && return 0; fi
    fi

    echo -- list files by echo...
    shopt -s globstar
    for FILE in $(echo **)
    do
        if [ ! -d $FILE ]
        then
            GREP=$(head $FILE | grep . | grep -v ^Binary || true)
            if [ "$GREP" ]; then echo $FILE; fi
        fi
    done
}

export -f write_empty
export -f list_files


# MAIN

if [ ! "$NOUPDATE" ]
then
    echo Update project config creator includes and files

    write_empty $NAME.config "// ADD PREDEFINED MACROS HERE!" \
        "#define __GXX_EXPERIMENTAL_CXX0X__ 1"

    write_empty $NAME.creator "[General]"

    write_empty $NAME.includes . \
        $(find . -name include | xargs echo) \
        /usr/include \
        /usr/local/include

    echo - create: $NAME.files
    list_files | grep -vxE "\..+" > $NAME.files
fi

echo Running Qt Creator for $NAME
qtcreator $NAME.creator >/dev/null 2>&1 &
cd "$CUR_DIR"

