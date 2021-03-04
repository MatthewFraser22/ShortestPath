

#ifndef GRAPH_H_
#define GRAPH_H_
#define INFINITY 99999

typedef struct adjnode {
	int vertex; // child node id of this edge
	int weight; // edge weight of this edge
	struct adjnode *next; //next connected node
} ADJNODE;

typedef struct graph {
	int order;         //number of nodes
	int size;          //number of edges
	ADJNODE **adjlist; //pointer to an array of pointers of neighbor adjacency list
} GRAPH;

/* create and return a new adjacent list graph of order n */
GRAPH *new_graph(int n);

/* add a new edge (from, to, weight) to the graph passed by GRAPH *g,
 * if the edge (from, to) exists, update its weight,
 * else add the new adjacency node to the end of the linked list of the from node
 */
void add_edge(GRAPH *g, int from, int to, int weight);

/* return the weight of edge (from, to) if exists,
 * otherwise return INFINITY
 */
int get_weight(GRAPH *g, int from, int to);

/* display the graph the proper format*/
void display_graph(GRAPH *g);

/* clean the graph by free all dynamically allocated memory*/
void clean_graph(GRAPH **gp);


#endif /* GRAPH_H_ */
