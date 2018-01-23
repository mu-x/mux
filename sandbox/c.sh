#!/bin/bash
set -e -x

SRC=
while [ "$1" ] && [ "$1" != "--" ]; do
    SRC+=" $1"
    shift
done
[ "$1" == "--" ] && shift

: ${SRC:=1.cpp}
COMPILER=${C:-g++}
STD=${S:-11}

OPTIONS="-std=c++$STD -fPIC -W -Wall -Wextra $O"
LIBS="-pthread $L"

for INCLUDE_DIR in $I; do
    OPTIONS+=" -I$INCLUDE_DIR"
done

for LIB_DIR in $LD; do
    OPTIONS+=" -L$LIB_DIR"
    LD_LIBRARY_PATH+=":$LIB_DIR"
done

if [ "$B" ]; then
    OPTIONS+=" -DBOOST -I/usr/include/boost"
    LIBS+="-lboost_system"
fi

if [ "$Q" ]; then
    OPTIONS+=" -DQT"
    [ -d /usr/include/qt$Q ] && OPTIONS+=" -I/usr/include/qt$Q"
    [ -d /usr/include/x86_64-linux-gnu/qt$Q ] && OPTIONS+=" -I/usr/include/x86_64-linux-gnu/qt$Q"
    LIBS+=" -lQt${Q}Core -lQt${Q}Network"
fi

$COMPILER $OPTIONS $SRC $LIBS
$R ./a.out $@
