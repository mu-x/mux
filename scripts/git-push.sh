#!/bin/bash
#
# mux: Git commit+fetch+rebase+push
#
set -e -x

BRANCH=${1:-${MUX_BRANCH:-master}}
SERVER=${2:-${MUX_SERVER:-gerrit}}
ORIGN=${3:-${MUX_ORIGIN:-origin}}

git commit -a --amend
git fetch $SERVER
git rebase $ORIGN/$BRANCH
git push $SERVER HEAD:refs/for/$BRANCH
