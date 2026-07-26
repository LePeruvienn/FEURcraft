#!/bin/bash

# USED TO CHECK FOR MEMORY USAGE OF AN EXE
#
# -h for HELP !
# -h for HELP !
# -h for HELP !

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
OUT_DIR="$SCRIPT_DIR/out"

# Fichier out par défaut
OUT="$OUT_DIR/massif_report.txt"

if [ $# -lt 1 ]; then
	echo "Usage : <binary> <out path [optional]>"
	exit 1
fi

if [ "$1" == "-h" ] ; then

	echo "This script is used to check for memory usage with valgrind"
	echo
	echo "Usage : <binary> <out path [optional]>"
	echo
	echo "Example :"
	echo " - ./check_memory.sh ./bin/my_exe"
	echo " - ./check_memory.sh ./bin/my_exe report.txt"

	exit 0
fi

if [ ! -z "$2" ]; then

	OUT=$2

	# on créer le dosser si il existe pas au cas ou
	mkdir -p "$OUT_DIR"

	echo "Out file is : $OUT"
fi

BIN_PATH="$1"

if [ ! -f "$BIN_PATH" ]; then
	echo "Executable path is invalid : $BIN_PATH"
	exit 2
fi

echo "--- Lancement du programme --- "

# Lancement du check mémoire
valgrind --tool=massif --massif-out-file="$OUT" "$BIN_PATH"

echo
echo "--- Fin du programme --- "
echo

echo "Analyse terminée. Rapport disponible dans : $OUT"
