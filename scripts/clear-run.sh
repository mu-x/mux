#!/bin/bash
#
# mux: Clear runs programs
#

set -e -x

export GTK2_RC_FILES=
export GTK_DATA_PREFIX=

$@
