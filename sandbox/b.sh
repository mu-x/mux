#!/bin/bash

source "$(dirname $(dirname $(readlink -f "${BASH_SOURCE[0]}")))/scripts/resources/tools.sh"

function main() {
    mux_title Hello World
}

main

