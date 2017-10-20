set -e -x
: ${CXX:=clang++-4.0}

FLAGS="-std=c++1z -Wall"
LIBS="-I/usr/include/x86_64-linux-gnu/qt5 -L/usr/lib/x86_64-linux-gnu -lQt5Core"

mkdir -p build
$CXX $FLAGS $LIBS src/markov_texts/*.cpp -shared -fPIC -o build/libmarkov_texts.so

LIBS+="-Isrc -L./build -lmarkov_texts"
$CXX $FLAGS src/parser.cpp $LIBS -o build/parser
$CXX $FLAGS src/generator.cpp $LIBS -o build/generator

if [ "$1" == "--build_and_run_ut" ]; then
    $CXX $FLAGS src/tests/*.cpp $LIBS -o build/tests
    LD_LIBRARY_PATH=./build build/tests
fi
