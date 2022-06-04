#include "args-parser.h"
#include "prim.h"
#include "parsing.h"
#include "djikstra.h"
#include "graphe.h"
#include "lib.h"
#include "tps_unit_test.h"



TEST_INIT_GLOBAL

void test_arbre_index(void)
{
    options_t options;
    initOptions(&options);

    options.outputFilename = "output.txt";

    Graphe* graphe = createGraph(options,&ListOfElemToFree);

    NodeAuthor* Paul=getAuthorSNode("Paul Kocher",graphe);

    tps_assert(strcmp(Paul->name,"Paul Kocher")==0);

    cleanOptions(&options);
}

int main()
{
   
    makeFile("fichier100Klignes","binaryFile");
    makeFile("smallXML","SmallBinaryFile");

    TEST(testGraphIndex);
    TEST(testCoAuthorsWithoutYear);
    TEST(testCoAuthorsWithYear);
    TEST(testFiles);
    TEST(testPlusCourtCheminCasParticuliers);
    TEST(testPlusCourtChemin);

    return 0;
}