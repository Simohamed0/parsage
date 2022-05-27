#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../include/parsing.h"
#include "../include/graphe.h"
#include "../include/lib.h"
#include "../include/prim.h"




int main(int argc, char *argv[]){
    
    if(argc != 4){
        printf("Usage: %s <input_file> <output_file> <output_file2>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");
    FILE *output_file_2 = fopen(argv[3], "w");
    if (input_file == NULL || output_file == NULL || output_file_2 == NULL){
        printf("Error opening file\n");
        return 1;
    }
    
    // NBR_NODE nodes stored in the tab_tree structure
    TreeNode *tab_tree = malloc((NBR_NODE)*sizeof(TreeNode));
    if (tab_tree == NULL){
        printf("Error allocating memory\n");
        return 1;
    }
    parse_csv(input_file, output_file, tab_tree);
    


    //Edge **graph = malloc((MAX_EDGE)*sizeof(Edge*));
    //if(graph == NULL){
    //    printf("Error allocating memory\n");
    //    return 1;
    //}
    //
    //for(int i = 0; i < MAX_EDGE; i++){
    //    graph[i] = malloc(MAX_EDGE*sizeof(Edge));
    //    if(graph[i] == NULL){
    //        printf("Error allocating memory\n");
    //        return 1;
    //    }
    //}
    //    
    //for (int i = 0; i < MAX_EDGE; i++) {
    //    for (int j = 0; j < MAX_EDGE; j++) {
    //        
    //        graph[i][j].node_id = tab_tree[i].id;
    //        graph[i][j].node_adj_id = tab_tree[j].id;
    //        graph[i][j].distance = distance(tab_tree[i].x, tab_tree[j].x, tab_tree[i].y, tab_tree[j].y);
    //        
    //        if( i == j ) {
    //            graph[i][j].distance = 0;
    //        }
    //    }
    //}

    //for (int i = 0; i < MAX_EDGE; i++){
    //    for(int j = 0; j < MAX_EDGE; j++){
    //        printf("%d %d %f\n", graph[i][j].node_id, graph[i][j].node_adj_id, graph[i][j].distance);
    //    }
    //    printf("\n");
    //}
    
    primMST(tab_tree,output_file_2);
       

    //for (int i = 0; i < MAX_EDGE; i++)
    //    free(graph[i]);
    // 
    //free(graph);
    free(tab_tree);
    fclose(input_file);
    fclose(output_file);
    fclose(output_file_2);
    return 0;
}

//
//

//
//int actionEncode(options_t *options) {
//    
//    int exitCode = encode(
//        options->outputFile, 
//        options->messageToEncode,
//        options->messageLength,
//        options->compressionFactor); 
//    if(exitCode != ENCODER_OK) 
//    {
//        fprintf(stderr, "error while encoding %i\n", exitCode);
//    }
//    return exitCode;
//}
//
//int main(int argc, char **argv) {
//    
//    int exitCode = 0;
//
//    options_t options;
//    
//    parseArgs(argc, argv, &options);
//
//    if(ENCODER_OK != (exitCode = openFiles(&options))) {
//        goto quit;
//    }
//
//    
//    switch(options.action) {
//        case ACTION_DECODE: 
//            exitCode = actionDecode(&options);
//            break;
//        case ACTION_ENCODE:
//            exitCode = actionEncode(&options);
//            break;
//        case ACTION_UNKNOWN:
//            fprintf(stderr, "action is missing\n");
//            exitCode = 4;
//    }
//
//
//    quit:
//
//    if(exitCode) 
//        fprintf(stderr, "%s\n", errorToString(exitCode));
//
//    cleanOptions(&options);
//    return exitCode;
//}



/**
 * There is more than one way to define "memory leak". In particular, there are two primary definitions of "memory leak" that are in common usage among programmers.

The first commonly used definition of "memory leak" is, "Memory was allocated and was not subsequently freed before the program terminated." However, many programmers (rightly) argue that certain types of memory leaks that fit this definition don't actually pose any sort of problem, and therefore should not be considered true "memory leaks".

An arguably stricter (and more useful) definition of "memory leak" is, "Memory was allocated and cannot be subsequently freed because the program no longer has any pointers to the allocated memory block." In other words, you cannot free memory that you no longer have any pointers to. Such memory is therefore a "memory leak". Valgrind uses this stricter definition of the term "memory leak".

This is the type of leak which can potentially cause significant heap depletion, especially for long lived processes.

The "still reachable" category within Valgrind's leak report refers to allocations that fit only the first definition of "memory leak". These blocks were not freed, but they could have been freed (if the programmer had wanted to) because the program still was keeping track of pointers to those memory blocks.

In general, there is no need to worry about "still reachable" blocks. They don't pose the sort of problem that true memory leaks can cause. For instance, there is normally no potential for heap exhaustion from "still reachable" blocks. This is because these blocks are usually one-time allocations, references to which are kept throughout the duration of the process's lifetime.

While you could go through and ensure that your program frees all allocated memory, there is usually no practical benefit from doing so since the operating system will reclaim all of the process's memory after the process terminates, anyway. 

Contrast this with true memory leaks which, if left unfixed, could cause a process to run out of memory if left running long enough, or will simply cause a process to consume far more memory than is necessary.

Probably the only time it is useful to ensure that all allocations have matching "frees" is if your leak detection tools cannot tell which blocks are "still reachable" (but Valgrind can do this) or if your operating system doesn't reclaim all of a terminating process's memory (all platforms which Valgrind has been ported to do this).
 * 
 */




