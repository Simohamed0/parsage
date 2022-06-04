#include "graphe.h"
#include "lib.h"
#include "parsing.h"


#include <limits.h>
#include <stdbool.h>
#include <stdio.h>



int minKey(int *key, int *mstSet , int nbr_node);

void printMST(int *parent,int *parent_aux, TreeNode *tab_tree,FILE *fd , int nbr_node);

int primMST(TreeNode *tab_tree, int nbr_node ,FILE *fd);


