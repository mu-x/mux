#!/bin/bash

set -e -x

CFLAGS="-std=c11 -Wall -Werror"

rm -rf ./build
mkdir ./build

gcc cch/*.c \
    $CFLAGS -pthread -fPIC -shared \
    -o build/libcch.so

gcc ./main.c \
    $CFLAGS -L./build -lcch \
    -o build/cch

if [[ "x" != "x$@" ]]; then
    LD_LIBRARY_PATH=./build ./build/cch "$@"
fi
