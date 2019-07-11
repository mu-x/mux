#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
CMake build helper script.
Usage:
    [OPTION=VALUE ...] $0 [target] [run-arguments]
Options:
    C - clean generate & build if set
	B - build directory, default: $PWD-build
	G - cmake generate flags to set
    K - keep current terminal output
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ ! "$K" ] && clear
[ "$X" ] && set -x

GENERATE_FLAGS="$G"
BUILD_DIR=${B:-"$PWD-build"}
[ "$C" ] && mux_trace_run rm -r "$BUILD_DIR"

BUILD_FLAGS="--build $BUILD_DIR"
[ "$1" ] && BUILD_FLAGS+=" --target $1"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
    GENERATE_FLAGS+=" -DCMAKE_CXX_FLAGS=' -fdiagnostics-color=always'"
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
[ "$2" ] && mux_trace_run $BUILD_DIR/bin/$@
