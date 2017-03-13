#!/bin/bash
#
#   Script to build and run yatest library, binaries and tasts
#
set -e -x
cd "$( dirname "${BASH_SOURCE[0]}" )"

# Environment variables
CXX=${CXX:-"g++"}
RUN=${RUN:-""}

# Configuration
COMMON_LIBS="-lpthread -lboost_system -lboost_filesystem"
FLAGS="$FLAGS -std=c++0x -Wall -I."

# Build dir according to archetecture
BUILD_DIR="./build_$(uname -m)"
mkdir -p "$BUILD_DIR"

# Build shared library
$CXX $FLAGS $COMMON_LIBS src/*.cpp -shared -fPIC -o "$BUILD_DIR/libyatest.so"

# Build client and server applications
BIN_LIBS="-L$BUILD_DIR -lyatest $COMMON_LIBS"
for PROGRAM in server client
do
    $CXX $FLAGS $PROGRAM.cpp $BIN_LIBS -o "$BUILD_DIR/yatest_$PROGRAM"
done

# Build and run tests if specified
TEST_LIBS="$BIN_LIBS $COMMON_LIBS -lgtest -lgtest_main"
if [[ "$@" == *test* ]]
then
    $CXX $FLAGS tests/*.cpp $TEST_LIBS -o "$BUILD_DIR/yatest_tests"
    RUN="$RUN" ./run.sh tests
    ./tests/binary_tests.sh
fi
