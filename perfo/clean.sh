#!/bin/bash

#####################################
#
#  Remove the out folder of the perfos
#
#####################################

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
BIN_DIR="$SCRIPT_DIR/../bin"

OUT_DIR="$SCRIPT_DIR/out"

rm -rf ${OUT_DIR}/*

echo "Cleaned perfo out dir : $OUT_DIR"

