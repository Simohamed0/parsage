#include "../include/prim.h"
// Number of vertices in the graph




// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int *key, int *mstSet)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < MAX_EDGE; v++)
		if (mstSet[v] == 0 && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}


// A utility function to print the
// constructed MST stored in parent[]
void printMST(int *parent,int *parent_aux, Edge **graph, FILE *fd)
{
    fprintf(fd,"Edge\t\t\t\tWeight\n");
    for (int i = 1; i < MAX_EDGE  ; i++)
        if ( parent[i] != 0 && graph[i][0].node_id != 0 )
            fprintf(fd,"%d - %d \t%lf \n", parent[i], graph[i][0].node_id , graph[parent_aux[i]][i].distance);
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
void primMST(Edge **graph,FILE *fd)
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
		for (int v = 0; v < MAX_EDGE; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v].distance && mstSet[v] == false && graph[u][v].distance < key[v])
			{
				parent[v] = graph[u][v].node_id;
				parent_aux[v] = u;
				key[v] = graph[u][v].distance;
			}
	}

	printMST(parent,parent_aux,graph,fd);
}
