#!/bin/sh

TARGET=bin/tree

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
# Compilation du programme.
#
annoncer "Compilation"
make clean
make $TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green

annoncer "Test 1  parsage "
$VALGRIND ./$TARGET -i les-arbres.csv -o output.csv  
echo "===DIFF===" >> $LOG
diff -Z output.csv tests/test1/sortie_attendue >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green

#sortie du test 2 est non nulle car les deux auteurs appartiennent à des composantes connexes disjointes

annoncer "Test 2"
$VALGRIND ./$TARGET -i tests/fichier100Klignes -o fichierBinaire -p "Paul Kocher" -p "Frank Manola" > tests/test2/sortieTest2 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test2/sortieTest2 tests/test2/sortieAttendueTest2 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green

annoncer "Test 3"
$VALGRIND ./$TARGET -i tests/fichier100Klignes -o fichierBinaire -p "Sandra Heiler" -p "Mark F. Hornick" > tests/test3/sortieTest3 2>&1 || fail
echo "===DIFF===" >> $LOG
diff -Z tests/test3/sortieTest3 tests/test3/sortieAttendueTest3 >> $LOG 2>&1 
if [ $? -ne 0 ]
then
    fail
fi
coloredEcho "OK" green

#sortie du test 2 est non nulle car les deux auteurs appartiennent à des composantes connexes disjointes pendant l'année 1993

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