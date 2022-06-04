#include "args-parser.h"
#include "prim.h"
#include "parsing.h"
#include "djikstra.h"
#include "graphe.h"
#include "lib.h"

#include "tps_unit_test.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

TEST_INIT_GLOBAL

void testGraphIndex(void)
{
    options options;
    initOptions(&options);

    options.PathFichierSortie="binaryFile";

    toFree ListOfElemToFree;
    Graphe* graphe=createGraph(options,&ListOfElemToFree);

    NodeAuthor* Paul=getAuthorSNode("Paul Kocher",graphe);

    tps_assert(strcmp(Paul->name,"Paul Kocher")==0);

    freeGraph(graphe,&ListOfElemToFree);
}

void testCoAuthorsWithoutYear(void)
{
    Options options;
    initOptions(&options);

    options.PathFichierSortie="binaryFile";

    toFree ListOfElemToFree;
    Graphe* graphe=createGraph(options,&ListOfElemToFree);

    NodeAuthor* Paul=getAuthorSNode("Paul Kocher",graphe);

    char* sortedListOfCoAuthors[9]={"Yuval Yarom","Werner Haas 0004",
    "Thomas Prescher 0002","Stefan Mangard","Moritz Lipp","Mike Hamburg",
    "Michael Schwarz 0001","Daniel Gruss","Daniel Genkin"};

    NoeudVoisin* voisinPaul=Paul->premierVoisin;

    for(int i=0;i<9;i++)
    {
        tps_assert(strcmp(voisinPaul->nomAuteur,sortedListOfCoAuthors[i])==0);
        voisinPaul=voisinPaul->suivant;
    }
    freeGraph(graphe,&ListOfElemToFree);
}

void testCoAuthorsWithYear(void)
{
    Options options;
    initOptions(&options);

    options.PathFichierSortie="SmallBinaryFile";
    options.yearEntred=True;

    toFree ListOfElemToFree;
    Graphe* graphe=createGraph(options,&ListOfElemToFree);

    char* sortedListOfCoAuthors[9]={"Yuval Yarom","Werner Haas 0004",
    "Thomas Prescher 0002","Stefan Mangard","Moritz Lipp","Mike Hamburg",
    "Michael Schwarz 0001","Daniel Gruss","Daniel Genkin"};

    int years[8]={2018,2017,2016,2015,2014,2013,2012,2011};

    NodeAuthor* Paul=getAuthorSNode("Paul Kocher",graphe);

    NoeudVoisin* voisinPaul=Paul->premierVoisin;

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<8;j++)
        {
            tps_assert(strcmp(voisinPaul->nomAuteur,sortedListOfCoAuthors[i])==0);
            tps_assert(voisinPaul->year==years[j]);
            voisinPaul=voisinPaul->suivant;
        }
    }
    freeGraph(graphe,&ListOfElemToFree);
}

void testFiles(void)
{
    File* fileTest=malloc(sizeof(File));

    Options options;
    initOptions(&options);

    options.PathFichierSortie="SmallBinaryFile";

    toFree ListOfElemToFree;
    Graphe* graphe=createGraph(options,&ListOfElemToFree);

    char* sortedListOfAuthors[9]={"Yuval Yarom","Werner Haas 0004",
    "Thomas Prescher 0002","Stefan Mangard","Moritz Lipp","Mike Hamburg",
    "Michael Schwarz 0001","Daniel Gruss","Daniel Genkin"};

    NodeAuthor* Paul=getAuthorSNode("Paul Kocher",graphe);

    fileTest->premierDansLaFile=Paul;
    fileTest->dernierDansLaFile=&Paul;
    enfilerPlusCourtChemin(fileTest,Paul,graphe,"NULL",False,options);

    int i=0;

    while(!fileEstVide(fileTest))
    {
        NodeAuthor* auteur=defilerFile(fileTest);
        tps_assert(strcmp(auteur->name,sortedListOfAuthors[i])==0);
        i++;
    }

    tps_assert(fileEstVide(fileTest));
    free(fileTest);
    freeGraph(graphe,&ListOfElemToFree);
}

void testPlusCourtCheminCasParticuliers(void)
{
    Options options;
    initOptions(&options);

    options.PathFichierSortie="SmallBinaryFile";

    toFree ListOfElemToFree;
    Graphe* graphe=createGraph(options,&ListOfElemToFree);

    // test premier auteur sans voisins
    options.nomAuteurUn="Auteur Sans Voisins";
    options.nomAuteurDeux="Paul Kocher";

    tps_assert(chercheLePlusCourtChemin(options,graphe)==SANS_VOISINS);

    //test deuxieme auteur sans voisins

    options.nomAuteurUn="Paul Kocher";
    options.nomAuteurDeux="Auteur Sans Voisins 2";

    tps_assert(chercheLePlusCourtChemin(options,graphe)==SANS_VOISINS);

    //test premier auteur n'existe pas

    options.nomAuteurUn="Premier Auteur N'existe pas";
    options.nomAuteurDeux="Paul Kocher";

    tps_assert(chercheLePlusCourtChemin(options,graphe)==AUTEUR_N_EXISTE_PAS);

    //test deuxieme auteur n'existe pas

    options.nomAuteurUn="Paul Kocher";
    options.nomAuteurDeux="Deuxieme Auteur N'existe pas";

    tps_assert(chercheLePlusCourtChemin(options,graphe)==AUTEUR_N_EXISTE_PAS);

    freeGraph(graphe,&ListOfElemToFree);
}

void testPlusCourtChemin(void)
{
    Options options;
    initOptions(&options);

    options.PathFichierSortie="SmallBinaryFile";

    toFree ListOfElemToFree;
    Graphe* graphe=createGraph(options,&ListOfElemToFree);

    //Les deux auteurs sont voisins

    options.nomAuteurUn="Paul Kocher";
    options.nomAuteurDeux="Daniel Genkin";

    tps_assert(chercheLePlusCourtChemin(options,graphe)==1);

    //Les deux auteurs sont voisins mais pas pendant l'année 2009

    ReinitAttributs(graphe);

    options.nomAuteurUn="Paul Kocher";
    options.nomAuteurDeux="Daniel Genkin";
    options.yearEntred=True;
    options.year=2009;

    tps_assert(chercheLePlusCourtChemin(options,graphe)==COMPOSANTES_CONNEXES_DISJOINTES);

    //Les deux auteurs sont à distance 2

    ReinitAttributs(graphe);

    options.nomAuteurUn="Paul Kocher";
    options.nomAuteurDeux="Auteur à distance 2 de Paul Kocher";
    options.yearEntred=False;
    
    tps_assert(chercheLePlusCourtChemin(options,graphe)==2);

    //Les deux auteurs sont à distance 2 mais à distance 4 pendant l'année 2018

    /**Ce chemin correspond à :
     * Paul Kocher
     * Yuval Yarum
     * Auteur Temp 1
     * Auteur Temp 2
     * Auteur à distance 2 de Paul Kocher
     * */

    ReinitAttributs(graphe);

    options.nomAuteurUn="Paul Kocher";
    options.nomAuteurDeux="Auteur à distance 2 de Paul Kocher";
    options.yearEntred=True;
    options.year=2018;

    tps_assert(chercheLePlusCourtChemin(options,graphe)==4);

    freeGraph(graphe,&ListOfElemToFree);

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