#!/bin/bash

# Couleurs pour l'affichage
GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
RESET="\033[0m"

# Chemin de l'exécutable
PHILO_EXEC="../philo"

# Affiche le titre principal
echo -e "${YELLOW}=====================================${RESET}"
echo -e "${YELLOW}            TEST PARSING            ${RESET}"
echo -e "${YELLOW}=====================================${RESET}"

# Tests d'erreur
error_tests=(
    # argc < 4
    "1 200 200"
    # argc > 5
    "1 200 200 200 5 extra"
    # Argument négatif
    "-1 200 200 200"
    "1 -200 200 200"
    "1 200 -200 200"
    "1 200 200 -200"
    # Premier argument est 0
    "0 200 200 200"
    # Argument NULL
    "1 200 200 ''"
    "1 200 '' 200"
    "1 '' 200 200"
    # Argument avec espaces uniquement
    "1 200 200 '   '"
    "1 200 '   ' 200"
    # Argument supérieur à INT_MAX
    "1 2147483648 200 200"
    # Argument inférieur à INT_MIN
    "1 -2147483649 200 200"
    # Double signe +
    "++1 200 200 200"
    "1 ++200 200 200"
    # Double signe -
    "--1 200 200 200"
    "1 --200 200 200"
    # Espace entre signe et chiffre
    "+ 1 200 200 200"
    "1 + 200 200 200"
    # Argument contenant deux chiffres séparés par un espace
    "1 '222 3455' 200 200"
)

# Tests de réussite
success_tests=(
    "1 200 200 200"
    "1 200 200 200 5"
    "5 400 100 200 9"
    "2 150 150 150"
    "10 500 300 200"
    "1 2147483647 100 100"
    "3 200 200 200"
    "4 400 300 200 7"
    "20 100 50 30 15"
    "1 1000 500 200"
	"1 1000 +500 +200"
	"1 200 200 00000000000000000000000000000000000200 5"
)

# Fonction pour exécuter un test
run_test() {
    local test_case="$1"
    local expected="$2"
    output=$($PHILO_EXEC $test_case 2>&1)
    local exit_code=$?

    if [[ "$expected" == "error" ]]; then
        if [[ $exit_code -ne 0 ]]; then
            echo -e "${GREEN}[PASS]${RESET} $PHILO_EXEC $test_case"
        else
            echo -e "${RED}[FAIL]${RESET} $PHILO_EXEC $test_case (Expected error)"
        fi
    else
        if [[ $exit_code -eq 0 ]]; then
            echo -e "${GREEN}[PASS]${RESET} $PHILO_EXEC $test_case"
        else
            echo -e "${RED}[FAIL]${RESET} $PHILO_EXEC $test_case (Expected success)"
        fi
    fi
}

# Exécution des tests d'erreur
echo -e "${RED}--- Tests d'erreur ---${RESET}"
for test in "${error_tests[@]}"; do
    run_test "$test" "error"
done

# Exécution des tests de réussite
echo -e "${GREEN}--- Tests de réussite ---${RESET}"
for test in "${success_tests[@]}"; do
    run_test "$test" "success"
done
