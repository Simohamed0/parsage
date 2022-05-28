#include "../include/prim.h"
// Number of vertices in the graph


// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int *key, int *mstSet)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < MAX_EDGE-1; v++)
		if (mstSet[v] == 0 && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}


// A utility function to print the
// constructed MST stored in parent[]
void printMST(int *parent,int *parent_aux, TreeNode *tab_tree, FILE *fd) {
    fprintf(fd,"Edge\t\t\t\tWeight\n");
    for (int i = 1; i < MAX_EDGE - 1  ; i++)
        if ( parent[i] != 0 && tab_tree->id != 0 ){
            double dis = distance(tab_tree[i].x,tab_tree[parent_aux[i]].x,tab_tree[i].y,tab_tree[parent_aux[i]].y);
			fprintf(fd,"%d - %d \t%lf \n", parent[i], tab_tree[i].id , dis);
		}
}

// Function to construct and print MST for a graph represented using adjacency matrix representation



/** This function is used to find the minimum spanning tree
* of the graph.
*
* @param graph : The graph to find the minimum spanning tree
* @param tree_id : The id of the tree to start with 
*
* @return : The minimum spanning tree
*/
void primMST(TreeNode *tab_tree, FILE *fd)
{
	// Array to store constructed MST
	int *parent = calloc(MAX_EDGE,sizeof(int));
	int *parent_aux = calloc(MAX_EDGE,sizeof(int));
    
	// Key values used to pick minimum weight edge in cut
	int *key=calloc(MAX_EDGE,sizeof(int));
    
	// To represent set of vertices included in MST
	int *mstSet = calloc(MAX_EDGE,sizeof(int));

	// Initialize all keys as INFINITE
	for (int i = 0; i < MAX_EDGE; i++) {
		
        key[i] = INT_MAX ;
        mstSet[i] = 0;
    }

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first vertex.
	key[0] = 0;
	parent[0] = -1; // First node is always root of MST
	parent_aux[0] = -1;

	double dis = 0.0;

	// The MST will have V vertices
	for (int count = 0; count < MAX_EDGE - 1; count++) {
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < MAX_EDGE ; v++)
		{
	
			if( u == v ) {
				dis = 0;
			}
			else {
				dis = distance(tab_tree[u].x, tab_tree[v].x, tab_tree[u].y, tab_tree[v].y);
			}
			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (dis && mstSet[v] == false && dis < key[v])
			{
				parent[v] = tab_tree[u].id;
				parent_aux[v] = u;
				key[v] = dis;
			}
		}
	}
	printMST(parent,parent_aux,tab_tree,fd);
	
	free(parent);
	free(parent_aux);
	free(key);
	free(mstSet);
}