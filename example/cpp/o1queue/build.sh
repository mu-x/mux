#!/bin/bash
#
#   Builds and runs tests, requires:
#   - GCC C++ Compiler 4.6.3+
#   - Google Test 1.6.0+
#

set -x -e
g++ -Wall *.cpp -lgtest -lgtest_main -pthread -o tests
./tests
