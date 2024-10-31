#!/bin/bash

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
SCRIPT_COMMAND="$(basename "$0")"
set -o nounset
set -o pipefail
set -o errexit
trap 'echo "$SCRIPT_COMMAND: error $? at line $LINENO"' ERR

. "${SCRIPT_DIR}"/icc-hack.sh

if enabled ; then
    "$0".original "$@"
else
    update_includes
    enable
    "$0".original "$@" || {
        ret=$?
        disable
        exit $?
    }
    disable
fi
