set -e -x

: ${CXX:=clang++-4.0}
: ${FLAGS:="-std=c++11 -Wall -fPIC -O2"}

LIB="markov_texts"
APPS="parser generator"

mkdir -p build
rm -rf build/*

FLAGS+=" -I/usr/include/x86_64-linux-gnu/qt5 -L/usr/lib/x86_64-linux-gnu -lQt5Core"
$CXX $FLAGS $LIBS src/$LIB/*.cpp -shared -o build/lib$LIB.so

LIBS+=" -I./src -L./build -l$LIB"
for APP in $APPS; do
    $CXX $FLAGS src/$APP.cpp $LIBS -o build/$APP
done

