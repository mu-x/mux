#!/bin/bash
set -e
cd $(dirname $0)

CXX="g++ -pthread -std=c++11 -rdynamic"
BUILD=""

for ARG in ${@:-def tcp udp}
do
    case $ARG in
        def) BUILD+=" mediator client peer" ;;
        tcp) BUILD+=" tcp_rev_public tcp_rev_private" ;;
        udp) BUILD+=" udp_mediator udp_peer" ;;
    esac
done

set -x
for TARGET in $BUILD
do
    $CXX ${TARGET}.cpp -o $TARGET
done

