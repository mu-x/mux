#!/bin/bash

set -e
[ $X ] && set -x

CXX=${CXX:-"clang++-6.0"}
CXX_FLAGS="-std=c++17 ${CXX_FLAGS:-"-Wall -Werror"}"
OUT_DIR=${OUT_DIR:-"./build"}
VERBOSE=${V:-$VERBOSE}

function build() {
  [ $VERBOSE ] && echo
  echo "----- Build: $1"

  local out=$OUT_DIR/$1; shift
  local command="$CXX $CXX_FLAGS $@ -o $out"
  
  [ $VERBOSE ] && echo $command
  $command
}

function run() {
  [ $VERBOSE ] && echo
  echo "##### Run: $1"

  local binary=$OUT_DIR/$1; shift
  local command="$binary $@"
  
  [ $VERBOSE ] && echo $command
  $command
}

rm -r "$OUT_DIR" 2>/dev/null || true
mkdir -p "$OUT_DIR"

build main $(echo src/*.cpp)
run main
