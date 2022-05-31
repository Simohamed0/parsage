#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


#define INF 999999999


#define MAX_EDGE 205
 

// Data structure to represent an edge in graph
typedef struct Edge{

    int node_id;
    int node_adj_id;
    double distance;
}Edge;

// Data structure to represent a graph
typedef struct Graph{

    Edge *tab_edge;
    int nbr_edge;
}Graph;


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






