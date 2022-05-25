#!/bin/sh

TARGET=bin/

#
# Ce placer dans le répertoire courant
#
TESTDIR="$(cd "$(dirname "$0}")" && pwd)"
cd "$TESTDIR"

#
# Conserver une trace de toutes les actions
#
LOG="test.log"
rm -f "$LOG"
touch "$LOG"

#
# Importer les fonctions communes à tous les tests
#
. ./fonctions.sh


#
# Compilation du programme.
#

annoncer "Compilation"
make clean
make $TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green


annoncer "Execution erreur"
$VALGRIND ./$TARGET -i NEXISTEPAS >> $LOG 2>&1 && fail
coloredEcho "OK" green

annoncer "Execution erreur 2"
$VALGRIND ./$TARGET -i tests/cat.bmp -o /NEXSTEPAS/OUT.TXT >> $LOG 2>&1 && fail
coloredEcho "OK" green


annoncer "Execution erreur 3"
$VALGRIND ./$TARGET -e -i tests/cat.bmp >> $LOG 2>&1 && fail
coloredEcho "OK" green




exit 0
