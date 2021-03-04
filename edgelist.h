
#ifndef EDGELIST_H_
#define EDGELIST_H_
/* structure of edge for the node of linked list of edge list
 */
typedef struct edge {
	int from;  // parent node id of the edge
	int to;    // child node id of the edge
	int weight; // weigh of the edge
	struct edge *next;  // pointer to the next edge
} EDGE;

/* the structure representing the graph by edge list
 */
typedef struct edgelist {
	int size;    //the number of edges
	EDGE *start; //pointer to the start of edge list
	EDGE *end;   //pointer to end of edge list
} EDGELIST;


/* create and return a new dynamically created edge list graph */
EDGELIST *new_edgelist();

/* add an new edge (from, to, weight) to the edge list graph
 * if the edge exists, update the weight
 * else insert the new edge node at the end of the linked list
 */
void add_edge_end(EDGELIST *g, int from, int to, int weight);

/* add an new edge at the start of the linked list of edges*/
void add_edge_start(EDGELIST *g, int from, int to, int weight);

/* get weight of the edge list graph,
 * i.e. the sum of all edge weights
 */
int weight_edgelist(EDGELIST *g);

/* display edge list graph*/
void display_edgelist(EDGELIST *g);

/* clean the graph by free all dynamically allocated memory*/
void clean_edgelist(EDGELIST **gp);


#endif /* EDGELIST_H_ */
