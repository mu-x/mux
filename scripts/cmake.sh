#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
CMake build helper script.
Usage:
    [OPTION=VALUE ...] $0 [target]
Options:
    C - clean generate & build if set
	F - cmake flags to set
	B - build directory, default: $PWD-build
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ "$X" ] && set -x

GENERATE_FLAGS="$F"
BUILD_DIR=${B:-"$PWD-build"}
[ "$C" ] && mux_trace_run rm -r "$BUILD_DIR"

BUILD_FLAGS="--build $BUILD_DIR"
if [ "$1" ]; then
	BUILD_FLAGS+=" --target $1"
	shift
fi

if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
    if mux_is_windows; then
        GENERATE_FLAGS+=" -Ax64 -Thost=x64"
    else
        GENERATE_FLAGS+=" -GNinja"
    fi
fi

if [ "$GENERATE_FLAGS" ]; then
	SRC_DIR="$PWD"
	cd "$BUILD_DIR"
	mux_trace_run cmake "$SRC_DIR" $GENERATE_FLAGS
	cd -
fi

mux_trace_run cmake $BUILD_FLAGS
