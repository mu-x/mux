#!/bin/bash
#
# Interface Manager build script.
#
# File: build.sh
# Author: Uskov M. V.
# Date: 2013-01-22


cd "$(dirname "${BASH_SOURCE[0]}")"

echo ">>> libinterface_manager.so - building..."
if g++ -shared -std=c++0x -ludev interface_manager.cpp \
        -o libinterface_manager.so; then
    echo "<<< Success!"
else
    echo "<<< Fail, check gcc and libudev installation..."
    exit 1
fi

echo ">>> interface_manager - building..."
if g++ -std=c++0x main.cpp ./libinterface_manager.so \
        -o interface_manager; then
    echo "<<< Success!"
else
    echo "<<< Fail, check gcc and libudev installation..."
    exit 1
fi
  
echo "Type ./interface_manager for start an application;"
echo "Type ./test.py for start a test for an application."
