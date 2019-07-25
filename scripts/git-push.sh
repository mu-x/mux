#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Git commit+fetch+rebase+push
Usage: $0 [BRANCH] [SERVER] [ORIGIN]
END
exit 0; fi

set -e
[ "$X" ] && set -x

source "$(dirname $(readlink -f "${BASH_SOURCE[0]}"))/resources/tools.sh"

BRANCH=${1:-${MUX_BRANCH:-master}}
SERVER=${2:-${MUX_SERVER:-$(git remote show | head -1)}}
ORIGIN=${3:-${MUX_ORIGIN:-origin}}
REFS=${R:-${MUX_REFS:-refs/for/}}

GIT="mux_trace_run git"
$GIT branch
$GIT log -1
$GIT st

read -p "C=commit, c=add&commit, A=amend, a=add&amend, -=none: " ACTION
case $ACTION in
    C) $GIT commit ;;
    c) $GIT commit -a ;;
    A) $GIT commit --ammend ;;
    a) $GIT commit -a --amend ;;
    -) echo skip ;;
    *) mux_fail Wrong answer: $ACTION ;;
esac

$GIT fetch $SERVER
$GIT rebase $ORIGIN/$BRANCH
$GIT push $SERVER HEAD:$REFS$BRANCH
