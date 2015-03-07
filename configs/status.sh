#!/bin/bash

cd $(dirname "${BASH_SOURCE[0]}")

for CONFIG in .*rc
do
    COMMAND="diff $HOME/$CONFIG $PWD/$CONFIG"
    echo $COMMAND
    $COMMNAD
done

echo Done
