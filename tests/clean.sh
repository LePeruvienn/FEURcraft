#!/bin/bash

#####################################
#
#  Remove the out folder of the tests
#
#####################################

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
BIN_DIR="$SCRIPT_DIR/../bin"

ASSETS_DIR="$SCRIPT_DIR/assets"
OUT_DIR="$SCRIPT_DIR/out"

rm -rf ${OUT_DIR}/*

echo "Cleaned tests out dir : $OUT_DIR"

