#!/bin/bash
set -e -x

SRC=
while [ "$1" ] && [ "$1" != "--" ]; do
    SRC+=" $1"
    shift
done
[ "$1" == "--" ] && shift

SRC=${F:-1.cpp}
COMPILER=${C:-g++}
STD=${S:-17}

OPTIONS="-std=c++$STD -fPIC $O"
LIBS="-pthread $L"

[ ! "$NW" ] && OPTIONS+=" -W -Wall -Wextra"

for INCLUDE_DIR in $I; do
    OPTIONS+=" -I$INCLUDE_DIR"
done

for LIB_DIR in $LD; do
    OPTIONS+=" -L$LIB_DIR"
    LD_LIBRARY_PATH+=":$LIB_DIR"
done

if [ "$B" ]; then
    OPTIONS+=" -DBOOST -isystem /usr/include/boost"
    LIBS+="-lboost_system"
fi

if [ "$Q" ]; then
    OPTIONS+=" -DQT"
    [ -d /usr/include/qt$Q ] && OPTIONS+=" -isystem /usr/include/qt$Q"
    [ -d /usr/include/x86_64-linux-gnu/qt$Q ] && OPTIONS+=" -I/usr/include/x86_64-linux-gnu/qt$Q"
    LIBS+=" -lQt${Q}Core -lQt${Q}Network"
fi

$COMPILER $OPTIONS $SRC $LIBS
$R ./a.out $@
