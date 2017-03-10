#!/bin/bash

if [[ "$1" == --help ]] || [[ "$1" == -h ]]; then cat <<END
Hg push after rebase in different folder.
Usage: mux-git-push [ID] [BRANCH]
END
exit 0; fi

if [ ! -d .hg ]; then
    echo "Error: This is not a HG repository." >&2
    exit 1
fi

set -e -x

ID=${1:-$(hg id -i | tr + ' ')}
BRANCH=${2:-$(hg branch)}

EDIT_DIR="$PWD"
PUSH_DIR="${EDIT_DIR}_push"
cd "$PUSH_DIR"

# Get and apply remote server state.
hg pull
hg update "$BRANCH"

# Get and rebase local changes.
hg pull "$EDIT_DIR"
hg phase --draft --force $ID
hg rebase --source $ID --dest $(hg id -i) || true

# Verify and push changes.
hg update
hg push

