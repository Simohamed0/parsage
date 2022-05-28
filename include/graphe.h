#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "parsing.h"

#define INF 999999999
#define NBR_NODE 205821

#define MAX_EDGE 205
 
typedef struct TreeNode{
    
    int id;
    double x;
    double y;

}TreeNode;

// Data structure to store an edge in the 
typedef struct Edge{

    int node_id;
    int node_adj_id;
    double distance;
}Edge;

/**
 * @brief erase the fisrt char c from the string
 * 
 * @param string 
 * @param x 
 */
void erase_char(char *string, char c);


/**
 * @brief insert a char c into the string at the position loc 
 * 
 * @param src string before changing
 * @param dst string after inserting
 * @param c   char to insert
 * @param loc position to insert
 */
void string_insert(char *src,char *dst ,char x, int loc);


/**
 * @brief parse a csv file line and save the information in a data structure
 * 
 * @param fscript file to parse
 * @param fout file to write the information 
 * @param tree_struct data structure to save the information
 */
void parse_csv(FILE *src, FILE *dst , TreeNode *tab_tree); 



// Define the maximum number of nodes in the graph




 
                                                        



///**
// * @brief Create a Graph object
// * 
// * @param n 
// * @param list_nodes 
// * @param graph
// * @return pointeur vers un graphe
// */
//Graph *createGraph(int n , TreeNode *list_nodes, Graph *graph);
//
//
///**
// * @brief delete graph object
// * 
// * @param graph 
// */
//void DeleteGraph(Graph *graph);





#endif






