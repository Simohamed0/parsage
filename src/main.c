#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../include/parsing.h"
#include "../include/graphe.h"
#include "../include/lib.h"
#include "../include/prim.h"
#include "../include/io-utils.h"
#include "../include/args-parser.h"
#include "../include/djikstra.h"



int main(int argc, char *argv[]){
    
    
    
    int exitCode = EXIT_SUCCESS;
    options_t options;
    parseArgs(argc, argv, &options);
    

    if(0 != (exitCode = openFiles(&options))) {
        goto quit;
    }
    

    if(exitCode != PARSAGE_OK) {
        
        fprintf(stderr, "error while parsing %i\n", exitCode);
    }

    action_parsage(&options);

    switch(options.action) {
    
        case ACTION_MST:
            exitCode = primMST(options.tree_tab, options.outputFile);
            break;
        case ACTION_DJKSTRA:
            Dijkstra(options.tree_tab, options.src_tree, options.outputFile);
            break;
        case ACTION_UNKNOWN:
            fprintf(stderr, "action is missing\n");
            exitCode = 4;
            break;
    }
    
    quit:
    //if(exitCode) 
        //fprintf(stderr, "%s\n", errorToString(exitCode));
    
    cleanOptions(&options);

    return 0;
}

//
//

//

//
//int main(int argc, char **argv) {
//    

//

//
//    

//
//
//    quit:
//

//
//    cleanOptions(&options);
//    return exitCode;
//}




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




