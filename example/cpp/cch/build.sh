#!/bin/bash

set -e -x

CFLAGS="-Wall -Werror"

rm -rf ./build
mkdir ./build

gcc cch/*.c \
    $CFLAGS -fPIC -shared \
    -o build/libcch.so

gcc main.c \
    $CFLAGS -L./build -lcch \
    -o build/cch

if [ "$@" ]; then
    LD_LIBRARY_PATH=./build ./build/cch "$@"
fi
