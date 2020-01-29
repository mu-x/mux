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
    TC  number of threads to build on, eg -j, overrides TS
    TS  threads to save, default ${MUX_THREAD_SAVE:-2}
Examples:
    B=./build G="-Dparameter=value" $0
    $0 some_module_ut --gtest_filter="SomeTest*"
END
exit 0; fi

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

set -e
[ ! "$K" ] && clear
[ "$X" ] && set -x

if [ "$1" ]; then
    TARGET="$1"
    shift
fi

GENERATE_FLAGS=($G)

SOURCE_DIR="$PWD"
mux_is_windows && SOURCE_DIR=../$(basename "$PWD")

BUILD_DIR=${B:-"$SOURCE_DIR-build"}
[ "$C" ] && mux_trace_run rm -r "$BUILD_DIR"

BUILD_FLAGS="--build $BUILD_DIR"
[ "$TARGET" ] && BUILD_FLAGS+=" --target $TARGET"

if [ -d .hg ]; then
    CHANGE_ID="hg-$(hg id | tr ' ' -)";
elif [ -d .git ]; then
    CHANGE_ID="git-$(git rev-parse HEAD)";
else
    CHANGE_ID="no vsc: $(date +%s)";
fi
BUILD_ID=$(cat "$BUILD_DIR"/ChangeId.txt 2>/dev/null || true)

FORCE_GENERATE=$FG
if [ "$CHANGE_ID" != "$BUILD_ID" ] || [ "$GENERATE_FLAGS" ] || [ "$FORCE_GENERATE" ]; then
    echo "Change: $CHANGE_ID, build: ${BUILD_ID:-none}, flags: ${GENERATE_FLAGS[@]}".
    [ "FORCE_GENERATE" ] && echo Force Generate!
    mkdir -p "$BUILD_DIR"
    if mux_is_windows; then
        GENERATE_FLAGS+=(-Ax64 -Thost=x64)
    else
        GENERATE_FLAGS+=(-GNinja -DCMAKE_CXX_FLAGS=' -fdiagnostics-color=always')
    fi
fi

if [ "$GENERATE_FLAGS" ]; then
    echo $CHANGE_ID > "$BUILD_DIR"/ChangeId.txt
	cd "$BUILD_DIR"
	mux_trace_run cmake "$SOURCE_DIR" "${GENERATE_FLAGS[@]}"
	cd -
fi

if mux_is_linux; then
    THREAD_COUNT=${TC:-$(( $(nproc) - ${TS:-${MUX_THREAD_SAVE:-2}} ))}
    BUILD_FLAGS+=" -- -j $THREAD_COUNT"
fi

mux_trace_run cmake $BUILD_FLAGS

if [[ "$@" ]]; then
    mux_is_windows && TARGET+=.exe
    BINARY_PATH=$(find "$BUILD_DIR" -name "$TARGET" -type f | head -1)
    [[ "x" == "x$BINARY_PATH" ]] && mux_fail No executable $BUILD_DIR .. $TARGET
    mux_trace_run "$BINARY_PATH" "$@"
fi

