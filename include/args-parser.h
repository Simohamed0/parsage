#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H
#include <stdio.h>
#include <inttypes.h>
#include "parsing.h"
#include "io-utils.h"


typedef enum action_t {
    
    ACTION_UNKNOWN,
    ACTION_MST,
    ACTION_DJKSTRA
} action_t;

/**
 * @brief Options that can be sent in the command line
 * 
 */
typedef struct options_t {
    
    action_t action;
    int src_tree;
    int dst_tree;
    char *inputFilename;
    char *outputFilename;
    FILE *inputFile;
    FILE *outputFile;
    TreeNode *tree_tab;
    
} options_t;

/**
 * @brief initialize the options structure
 * 
 * @param options 
 */
void init_options(options_t *options);

void parseArgs(int argc, char **argv, options_t *options);

void cleanOptions(options_t *options);

/**
 * @brief call the parser function and check the result
 * 
 * @param options 
 */
int action_parsage(options_t *options);

/**
 * @brief open the files and check the opening
 * 
 * @param options 
 * @return 0 if the files are opened successfully, ERROR_OPENING_FILES otherwise
 */
int openFiles(options_t *options);

#endif
