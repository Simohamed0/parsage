#!/bin/sh

TARGET=bin/tree

#
# Ce placer dans le répertoire courant
#
TESTDIR="$(cd "$(dirname "$0}")" && pwd)"
cd "$TESTDIR"

#
# importer les fonctions definies dans fonctions.sh
#
. ./fonctions.sh

#
# Conserver une trace de toutes les actions
#
LOG="test.log"
rm -f "$LOG"
touch "$LOG"

#
# Compilation du programme.
#
annoncer "Compilation"
make clean
make $TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green


annoncer "Test 1  parsage du fichier "
$VALGRIND ./$TARGET -i les-arbres.csv -o tests/test1/sortieTest 
echo "===DIFF===" >> $LOG
diff -Z tests/test1/sortie_attendue tests/test1/sortieTest >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green



annoncer "Test 2 prim sur data_test"
$VALGRIND ./$TARGET -i data_test.csv -o tests/test2/sortieTest2 -p 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test2/sortieTest2 tests/test2/sortie_attendu2 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green

annoncer "Test 3 djikstra from source 3"
$VALGRIND ./$TARGET -i data_test.csv -o tests/test3/sortieTest3 -d 3 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test3/sortieTest3 tests/test3/sortie_attendue3 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green

annoncer "Test 4 prim sur tout le fichier un peu long.."
$VALGRIND ./$TARGET -i les-arbres.csv -o tests/test4/sortieTest4 -p 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test4/sortieTest4 tests/test4/sortie_attendu4 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green


annoncer "Test 4"
$VALGRIND ./$TARGET -i tests/fichier100Klignes -o fichierBinaire -p "Sandra Heiler" -p "Mark F. Hornick" -y 1993 > tests/test4/sortieTest4 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test4/sortieTest4 tests/test4/sortieAttendueTest4 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail 
fi
coloredEcho "OK" green

#test de nombre de composantes connexes dans le petit fichier XML qui sont 3 vu que auteur sans voisin
#et auteur sans voisin 2 existent

annoncer "Test 5"
$VALGRIND ./$TARGET -i tests/smallXML -o fichierBinaire -p "Paul Kocher" -p "Daniel Gruss" -c > tests/test5/sortieTest5 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test5/sortieTest5 tests/test5/sortieAttendueTest5 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green

rm -rf fichierBinaires