#!/bin/bash
set -e -x

g++ BinaryTreeTest.cpp && ./a.out

g++ ClassicSortTest.cpp && ./a.out
g++ ClassicSortTest.cpp --std=c++11 -DTHREAD_CXX11 -pthread && ./a.out
