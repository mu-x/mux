#!/bin/bash
set -e -x

TARGET=fme
DIR="$(dirname "${BASH_SOURCE[0]}")"

g++ "$DIR/"*.cpp -o "$DIR/$TARGET"
$DIR/$TARGET
