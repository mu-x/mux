#!/bin/bash
#
# mux-git-push [BRANCH] [SERVER] [ORIGIN]
#   Git commit+fetch+rebase+push
#

set -e -x

BRANCH=${1:-${MUX_BRANCH:-master}}
SERVER=${2:-${MUX_SERVER:-$(git remote show | head -1)}}
ORIGIN=${3:-${MUX_ORIGIN:-origin}}
REFS=${R:-${MUX_REFS:-refs/for/}}

git commit -a --amend
git fetch $SERVER
git rebase $ORIGIN/$BRANCH
git push $SERVER HEAD:$REFS$BRANCH
