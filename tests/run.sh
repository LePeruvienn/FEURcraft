#!/bin/bash

#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !
#            USE -h FOR HELP !

######################################
#
#         LANCEUR DE TESTS
#
# $ run_test              |-> Lance tous les tests
# $ run_test test1 test2  |-> Lance uniquement les tests passés en paramètres
# $ run_test [args] -X    |-> Affiche le stdout des tests
#
######################################

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
BIN_DIR="$SCRIPT_DIR/../bin"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

STDOUT_ON=0
TEST_FILES=()

file_amount=0
test_amount=0
ko_amount=0

run_test() {

	local test_file=$1
	local test_name=$(basename "$1")

	if [ -x "$test_file" ]; then

		if [ "$STDOUT_ON" -eq 1 ]; then
			echo
			echo -e "${CYAN}[ $test_name ]${NC} Running..."
			"$test_file"
		else
			"$test_file" &> /dev/null
		fi

		local status=$?

		printf "${BLUE}[ %-20s ]${NC} : " "$test_name"

		test_amount=$((test_amount + 1))

		if [ "$status" -eq 0 ]; then
			echo -e "${GREEN}OK${NC} (fails : $status)"
		else
			echo -e "${RED}FAILED${NC} (fails : $status)"
			ko_amount=$((ko_amount + 1))
		fi

	else
		echo -e "${YELLOW}[SKIP]${NC} $test_name (not executable or not found)"
	fi
}

for arg in "$@"; do
	case "$arg" in
		-X)
			export FEUR_Tests_Enable_Minimal_Output=1
			STDOUT_ON=1
			;;
		-h|--help)
			echo "Usage: $0 [-X] [tests...]"
			echo
			echo "  run_test              Lance tous les tests"
			echo "  run_test test1 test2  Lance les tests spécifiés"
			echo "  run_test -X           Affiche le stdout des tests"
			exit 0
			;;
		-*)
			echo -e "${RED}Option inconnue : $arg${NC}"
			exit 1
			;;
		*)
			TEST_FILES+=("$BIN_DIR/$arg.tst")
			file_amount=$((file_amount + 1))
			;;
	esac
done

echo
echo -e "${BOLD}${CYAN}========== Running tests ==========${NC}"
echo

if [ "$file_amount" -eq 0 ]; then
	shopt -s nullglob
	for f in "$BIN_DIR"/*.tst; do
		run_test "$f"
	done
else
	for f in "${TEST_FILES[@]}"; do
		run_test "$f"
	done
fi

passed=$((test_amount - ko_amount))

echo
echo -e "${BOLD}============== Summary ==============${NC}"
echo -e " ${GREEN}Passed${NC} : $passed"
echo -e " ${RED}Failed${NC} : $ko_amount"
echo -e " Total  : $test_amount"
echo

if [ "$test_amount" -ge 1 ]; then

	if [ "$ko_amount" -eq 0 ]; then
		echo -e "${GREEN}✔ Juste le GOAT en fait B)${NC}"
	elif [ "$ko_amount" -eq "$test_amount" ]; then
		echo -e "${RED}✘ Bro... tu troll là :(${NC}"
	elif [ "$ko_amount" -gt 0 ]; then
		echo -e "${YELLOW}⚠ Quelques tests ont échoué.${NC}"
	fi

fi
