#!/bin/bash
#
#   Script to run compiled binaries
#
cd "$( dirname "${BASH_SOURCE[0]}" )"

BUILD_DIR=${BUILD_DIR:-"./build_$(uname -m)"}

BINARY="$BUILD_DIR/yatest_$1"
ARGS="$2 $3 $4 $5 $6 $7 $8 $9"

LD_LIBRARY_PATH="$BUILD_DIR" $RUN "$BINARY" $ARGS
