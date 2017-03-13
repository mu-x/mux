#!/bin/bash
set -e -x

SRC=${@:-1.cpp}
COMPILER=${C:-g++}
STD=${S:-11}

OPTIONS="-std=c++$STD -fPIC -W -Wall -Wextra $O"
LIBS="-pthread $L"

if [ "$B" ]; then
    OPTIONS+=" -DBOOST"
fi

if [ "$Q" ]; then
    OPTIONS+=" -DQT -I/usr/include/qt$Q"
    LIBS+=" -lQt${Q}Core -lQt${Q}Network"
fi

$COMPILER $OPTIONS $SRC $LIBS
./a.out
