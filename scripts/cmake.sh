#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
CMake build helper script.
Usage:
    [OPTION=VALUE ...] $0 [target] [run-arguments]
Options:
    C   clean generate & build if set
    B   build directory, default: $PWD-build
    G   cmake generate flags to set
    FG  force cmake generate (enabled on G)
    K   keep current terminal output
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ ! "$K" ] && clear
[ "$X" ] && set -x

GENERATE_FLAGS=($G)
BUILD_DIR=${B:-"$PWD-build"}
[ "$C" ] && mux_trace_run rm -r "$BUILD_DIR"

BUILD_FLAGS="--build $BUILD_DIR"
[ "$1" ] && BUILD_FLAGS+=" --target $1"

CHANGE_ID=
[ -d .hg ] && CHANGE_ID=$(hg id)
[ -g .git ] && CHANGE_ID=$(git rev-parse HEAD)
BUILD_ID=$(cat "$BUILD_DIR"/ChangeId.txt 2>/dev/null || true)

FORCE_GENERATE=$FG
if [ "$CHANGE_ID" != "$BUILD_ID" ] || [ "$GENERATE_FLAGS" ] || [ "$FORCE_GENERATE" ]; then
    echo "Change: $CHANGE_ID, Build: $BUILD_ID, Flags: ${GENERATE_FLAGS[@]}".
    [ "FORCE_GENERATE" ] && echo Force Generate!
    mkdir -p "$BUILD_DIR"
    if mux_is_windows; then
        GENERATE_FLAGS+=(-Ax64 -Thost=x64)
    else
        GENERATE_FLAGS+=(-GNinja)
    fi
    GENERATE_FLAGS+=(-DCMAKE_CXX_FLAGS=' -fdiagnostics-color=always')
fi

if [ "$GENERATE_FLAGS" ]; then
	SRC_DIR="$PWD"
    echo $CHANGE_ID > "$BUILD_DIR"/ChangeId.txt
	cd "$BUILD_DIR"
	mux_trace_run cmake "$SRC_DIR" "${GENERATE_FLAGS[@]}"
	cd -
fi

mux_trace_run cmake $BUILD_FLAGS
[ "$2" ] && mux_trace_run $BUILD_DIR/bin/$@
