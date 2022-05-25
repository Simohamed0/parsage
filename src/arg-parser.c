

#include "args-parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>


void cleanOptions(options_t *options) {

    if(options->inputFile)
        fclose(options->inputFile);
    if(options->outputFile)
        fclose(options->outputFile);
}



void initOptions(options_t *options) {
    
    options->action = ACTION_UNKNOWN;
    options->inputFilename = NULL;
    options->outputFilename = NULL;
    options->inputFile = NULL;
    options->outputFile = NULL;
 
}

void checkOptionsValidity(options_t *options) {
    
    if(options->action == ACTION_MST) {

        fprintf(stderr, "encode action requires an input and output file\n");
        exit(1);
        
    } else {

        if(options->inputFilename == NULL) {
            fprintf(stderr, "encode action requires an input file.\n");
            exit(2);
        }
    }

}


void print_usage(void)
{
    printf("\n"
    "options:\n"
    "\t-i FICHIER    indiquer le fichier csv a ouvrir\n"
    "\t-o FICHIER    indiquer le fichier ou est sauvegarder le résultat\n"
    "\t-p            MST\n"
    "\t-h            for help \n"
    "exemlpe\n"
    "./tree data_test.csv output.txt\n");
}


void parseArgs(int argc,  char **argv, options_t *options) {


    initOptions(options);

    int c;
    while ((c = getopt (argc, argv, "hedf:i:o:m:")) != -1) 
    {
        switch (c)
        {
            case 'p':
                options->action = ACTION_MST;
                break;
            case 'd':
                options->action = ACTION_DIJKSTRA;
                break;
            case 'i':
                options->inputFilename = optarg;
                break;
            case 'o':
                options->outputFilename = optarg;
                break;
            case 'h':
                print_usage(); 
                exit(0);
                break;

            case '?':
                if (optopt == 'i' 
                    || optopt == 'o' ){
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                    print_usage();}
                else if (isprint (optopt)){
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                    print_usage();}
                else
                    {
                        fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                        print_usage();
                abort();
            default:
                abort ();
        }
    }

    checkOptionsValidity(options);
    }
}