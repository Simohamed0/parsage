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

    free(options->tree_tab);
}


void checkOptionsValidity(options_t *options) {
    
    if(options->action == ACTION_MST) {
        if(options->inputFilename == NULL || options->outputFilename== NULL) {
            fprintf(stderr, "MST action requires an input to parse and output file to write the result\n");
            exit(1);
        }

    } else {

        if(options->inputFilename == NULL) {
            fprintf(stderr, "MST action requires an input file.\n");
            exit(2);
        }
    }

}


void print_usage(void)
{
    printf("\n"
    "options:\n"
    "\t-i FICHIER    indiquer le fichier csv à traiter\n"
    "\t-o FICHIER    indiquer le fichier ou sauvegarder le résultat\n"
    "\t-p            MST\n"
    "\t-d src_index  Djikstra \n"
    "\t-t dst_index  Djikstra \n"         
    "\t-h            for help \n"
    "exemlpe\n"
    "./tree i- les-arbres.csv o- output.txt -p\n");
}


void parseArgs(int argc,  char **argv, options_t *options) {


    init_options(options);

    int c;
    while ((c = getopt (argc, argv, "hpd:i:o:t:")) != -1) 
    {
        switch (c)
        {
            case 'p':
                options->action = ACTION_MST;
                break;
            case 'i':
                options->inputFilename = optarg;
                break;
            case 'o':
                options->outputFilename = optarg;
                break;
            case 'd':
                options->action = ACTION_DJKSTRA;
                options->src_tree = atoi(optarg);
                break;
            case 't':
                if (options->action != ACTION_DJKSTRA) {
                    print_usage();
                    abort();
                }
                options->dst_tree = atoi(optarg);
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
                abort();
        }
    }

    checkOptionsValidity(options);
    }
}


int action_parsage(options_t *options){
    
    int nbr_node = parse_csv( options->inputFile, options->outputFile, options->tree_tab); 
    
    if(nbr_node <= 0) 
    {
        fprintf(stderr, "error while parsing \n");
    }
    return nbr_node;
}


int openFiles(options_t *options) {
    
    int exitCode = 0;
    
    if(options->inputFilename) {
        options->inputFile = fopen(options->inputFilename, "r");
        if(!options->inputFile) {
            fprintf(stderr, "error while opening input file %s\n", options->inputFilename);
            exitCode = ERROR_OPENING_FILES;
        }
    }
    if(options->outputFilename) {
        options->outputFile = fopen(options->outputFilename, "w");
        if(!options->outputFile) {
            fprintf(stderr, "error while opening output file %s\n", options->outputFilename);
            exitCode = ERROR_OPENING_FILES;
        }
    }
    return exitCode;
}

void init_options(options_t *options){

    options->action = ACTION_UNKNOWN;
    options->inputFilename = NULL;
    options->outputFilename = NULL;
    options->inputFile = NULL;
    options->outputFile = NULL;
    options->tree_tab = calloc(NBR_NODE ,sizeof(TreeNode));
    if ( !options->tree_tab ) {

        fprintf(stderr, "Error: malloc failed for tree_tab\n");
        exit(EXIT_FAILURE);
    }
}