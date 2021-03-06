#include "djikstra.h"

#define INFINIE 999999999


void Dijkstra(TreeNode *tab_tree, int startId, FILE *file , int nbr_node) {
  
      double dist[nbr_node];
      //int pred[NBR_NODE];
      int visited[nbr_node], count, mindist, nextnode, i;
      
      // Initialize dist and visited and pred
  
      int startIndex = treeIndex(tab_tree, startId);
  
      for (i = 0; i < nbr_node; i++) {
        dist[i] = distance(tab_tree[startIndex].x, tab_tree[i].x, tab_tree[startIndex].y, tab_tree[i].y);
        //pred[i] = startId;
        visited[i] = 0;
      }
  
      dist[startIndex] = 0;
      visited[startIndex] = 1;
      count = 1;
  
      while (count < nbr_node - 1) {
          mindist = INFINIE;
          double dis;
          for (i = 0; i < nbr_node; i++)
            if (dist[i] < mindist && !visited[i]) {
              mindist = dist[i];
              nextnode = i;
            }
  
          visited[nextnode] = 1;
          for (i = 0; i < nbr_node; i++)
              if (!visited[i]){
                  dis = distance(tab_tree[nextnode].x, tab_tree[i].x, tab_tree[nextnode].y, tab_tree[i].y);
                  if (mindist + dis < dist[i]) {
                    dist[i] = mindist + dis;
                    //pred[i] = treeId(tab_tree,nextnode);
                  }
              }
          count++;
    }

    // Printing the dist
    for (i = 0; i < nbr_node; i++){
        if (i != startIndex && treeId(tab_tree,i) > 0) {
            fprintf(file,"\ndist from source to %d: %lf\n", treeId(tab_tree,i), dist[i]);
        }
    }
}