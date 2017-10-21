set -e -x

: ${CXX:=clang++-4.0}
: ${FLAGS:="-std=c++11 -Wall -fPIC"}

LIB="markov_texts"
APPS="parser generator"

if [[ "$@" != *--skip-build* ]]; then
    mkdir -p build
    rm -rf build/*

    FLAGS+=" -I/usr/include/x86_64-linux-gnu/qt5 -L/usr/lib/x86_64-linux-gnu -lQt5Core"
    $CXX $FLAGS $LIBS src/$LIB/*.cpp -shared -o build/lib$LIB.so

    LIBS+=" -I./src -L./build -l$LIB"
    for APP in $APPS; do
        $CXX $FLAGS src/$APP.cpp $LIBS -o build/$APP
    done
fi

# TODO: Make a lot more tests with args.
if [[ "$@" == *--run-tests* ]]; then
    for APP in parser generator; do
        for TEST in "tests/$APP*test"; do
            if cat $TEST | LD_LIBRARY_PATH=./build build/$APP >/tmp/ok 2>/tmp/error; then
                diff $TEST.ok /tmp/ok
            else
                diff $TEST.error /tmp/error
            fi
        done
    done
fi
