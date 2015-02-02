#!/bin/bash

cat > /tmp/expected <<EOF
std
const
void
string
virtual
entry
public
children
include
path
EOF

./run.sh server & sleep 1; ./run.sh client tests > /tmp/executed
pkill yatest_server

DIFF=$(diff /tmp/expected /tmp/executed)
if [[ "$DIFF" ]]; then
    echo Failure
    echo $DIFF
    exit 1
else
    echo Success
fi
