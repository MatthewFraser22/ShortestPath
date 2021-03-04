
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

GRAPH *new_graph(int vertex_number) {
	GRAPH *ng = malloc(sizeof(GRAPH));
	ADJNODE **np = malloc(vertex_number * sizeof(ADJNODE*));

	int i;

	for (i = 0; i < vertex_number; i++)
		np[i] = NULL;

	ng->adjlist = np;
	ng->order = vertex_number;
	ng->size = 0;
	return ng;


}

/* add a new edge (from, to, weight) to the graph passed by GRAPH *g,
 * if the edge (from, to) exists, update its weight,
 * else add the new adjacency node to the end of the linked list of the from node
 */
void add_edge(GRAPH *g, int from, int to, int weight) {
// your implementation
	//error case
	if (0 > from || from > weight || 0 > to || to > weight) {
		return;
	}
	//pointer to prev and pointer to starting point
	ADJNODE *prev = NULL, *ptr = g->adjlist[from];


	while (ptr != NULL) {
		if (ptr->vertex == to) {
			//g->adjlist[from]->weight = weight;
			return;
		} else {
			prev = ptr;
			ptr = ptr->next;
		}
	}

	if (ptr == NULL) {
		ADJNODE *np = (ADJNODE *) malloc(sizeof(ADJNODE));
		np->vertex = to;
		np->next = NULL;
		np->weight = weight;
		if (prev == NULL) {
			g->adjlist[from] = np;
		} else {
			prev->next = np;
		}

	}

	g->size++;
	return;



}

int get_weight(GRAPH *g, int from, int to) {

	ADJNODE *prev = NULL, *ptr = g->adjlist[from];

	while (ptr != NULL) {
		if (ptr->vertex == to) {
			return ptr->weight;
		}
		prev = ptr;
		ptr = ptr->next;

	}

	return 0;

}

void clean_graph(GRAPH **gp) {
	int i;
	(*gp)->size = 0;
	(*gp)->order = 0;
	ADJNODE *temp, *ptr;
	int n = (*gp)->order;
	for (i = 0; i < n; i++) {
		ptr = (*gp)->adjlist[i];
		while (ptr != NULL) {
			temp = ptr;
			ptr = ptr->next;
			free(ptr);
		}
		(*gp)->adjlist[i] = NULL;

	}


}

void display_graph(GRAPH *g) {

	if (g == NULL)
		return;
	printf("\nweighted graph in adjacency list");
	printf("\norder: %d", g->order);
	printf("\nsize: %d", g->size);
	printf("\nnode from: (to weight)");
	int i;
	ADJNODE *ptr;
	for (i = 0; i < g->order; i++) {
		printf("\nnode %d:", i);
		ptr = g->adjlist[i];
		while (ptr != NULL) {
			printf(" (%d, %d)", ptr->vertex, ptr->weight);
			ptr = ptr->next;
		}
	}
}

