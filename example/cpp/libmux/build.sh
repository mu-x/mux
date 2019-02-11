#!/bin/bash

set -e
cd $(dirname $(readlink -f $0))

: ${CXX:=g++}
: ${STD:=c++17}
: ${FLAGS:="-Wall -Werror"}
: ${BUILD:="./build"}

function build() {
    TARGET="$1"; shift
    set -x
    $CXX -std=$STD $FLAGS -I./include -o "$BUILD/$TARGET" "$@"
    { set +x; } 2>/dev/null
}

rm -r "$BUILD" || true
mkdir -p "$BUILD"

build libmux.so -fPIC -shared src/mux/*.cpp
build tests -L"$BUILD" -lmux -I../catch2/single_include tests/*.cpp

"$BUILD/tests"
