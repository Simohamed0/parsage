#include "graphe.h"
#include "lib.h"
#include "parsing.h"


#include <limits.h>
#include <stdbool.h>
#include <stdio.h>



int minKey(int *key, int *mstSet);

void printMST(int *parent,int *parent_aux, TreeNode *tab_tree,FILE *fd);

int primMST(TreeNode *tab_tree,FILE *fd);


