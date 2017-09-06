#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Git commit+fetch+rebase+push
Usage: $0 [BRANCH] [SERVER] [ORIGIN]
END
exit 0; fi

set -e -x

BRANCH=${1:-${MUX_BRANCH:-master}}
SERVER=${2:-${MUX_SERVER:-$(git remote show | head -1)}}
ORIGIN=${3:-${MUX_ORIGIN:-origin}}
REFS=${R:-${MUX_REFS:-refs/for/}}

git commit -a --amend
git fetch $SERVER
git rebase $ORIGIN/$BRANCH
git push $SERVER HEAD:$REFS$BRANCH
