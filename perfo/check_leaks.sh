#!/bin/bash

# USED TO CHECK FOR MEMORY LEAKS OF AN EXE
#
# -h for HELP !
# -h for HELP !
# -h for HELP !

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
OUT_DIR="$SCRIPT_DIR/out"

# Fichier out par défaut
OUT="$OUT_DIR/valgrind_report.txt"

if [ $# -lt 1 ]; then
	echo "Usage : <binary> <out path [optional]>"
	exit 1
fi

if [ "$1" == "-h" ] ; then

	echo "This script is used to check for memoery leaks with valgrind"
	echo
	echo "Usage : <binary> <out path [optional]>"
	echo
	echo "Example :"
	echo " - ./check_leaks.sh ./bin/my_exe"
	echo " - ./check_leaks.sh ./bin/my_exe report.txt"

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

# Lancement du check de leak
valgrind --leak-check=full --track-origins=yes --log-file="$OUT" "$BIN_PATH"

echo
echo "--- Fin du programme --- "
echo

echo "Analyse terminée. Rapport disponible dans : $OUT"
