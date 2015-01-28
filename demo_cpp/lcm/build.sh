#!/bin/bash
#
#   LCM build script
#
set -e
cd "$( dirname "${BASH_SOURCE[0]}" )"


TARGET=lcm
SOURCES=$(echo *.cpp)

BUILD="g++ $SOURCES -pthread -o $TARGET"


echo Buildind bunary:
echo $BUILD
time $BUILD
echo Done!

if [[ ! "$@" =~ test ]]
then
    exit 0
fi


echo
echo Running tests:

function run_test {
    echo
    echo Run $1 test ...
    time ./lcm < $1.test > /tmp/res
    diff /tmp/res $2.result
    echo Success!
}

run_test tests/small tests/small
run_test tests/medium tests/medium
run_test tests/big tests/big

if [[ ! "$@" =~ long ]]
then
    echo
    echo Done!
    exit 0
fi

cat tests/big.test{,}{,}{,}{,}{,}{,}{,}{,}{,}{,} > /tmp/big1k.test
run_test /tmp/big1k tests/big

cat /tmp/big1k.test{,}{,}{,}{,}{,}{,}{,}{,}{,}{,} > /tmp/big1m.test
run_test /tmp/big1m tests/big

rm /tmp/big1k.test /tmp/big1m.test
echo
echo Done!
