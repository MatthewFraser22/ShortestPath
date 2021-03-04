

#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"

EDGELIST *new_edgelist() {
	EDGELIST *nl = (EDGELIST *) malloc(sizeof(EDGELIST));
	nl->size = 0;
	nl->end = NULL;
	nl->start = NULL;
	return nl;
}
EDGE *new_edge(int from, int to, int weight) {
	EDGE *ne = (EDGE *) malloc(sizeof(EDGE));
	ne->from = from;
	ne->to = to;
	ne->weight = weight;
	ne->next = NULL;
	return ne;
}
/* add an new edge (from, to, weight) to the edge list graph
 * if the edge exists, update the weight
 * else insert the new edge node at the end of the linked list
 */
void add_edge_end(EDGELIST *g, int from, int to, int weight) {
	EDGE *ep = new_edge(from, to, weight);

	if (g->start == NULL) {
		g->start = ep;
		g->end = ep;
		g->size++;
	} else {
		EDGE *current = g->start;
		while (!(current->from == from && current->to == to)
				&& current->next != NULL) {
			current = current->next;
		}
		if (current->from == from && current->to == to) {
			current->weight = weight;
		} else {
			current->next = ep;
			g->end = ep;
			g->size++;
		}
	}


}

void add_edge_start(EDGELIST *g, int from, int to, int weight) {
	EDGE *ne = new_edge(from, to, weight);
	if (g->start == NULL) {
		g->start = ne;
		g->end = ne;

	} else {
		ne->next = g->start;
		g->start = ne;
	}

	g->size++;
}

int weight_edgelist(EDGELIST *g) {
	if (g->start == NULL) {
		return 0;
	}
	int total = 0;
	EDGE *ne = g->start;
	while (ne != NULL) {
		total += ne->weight;
		ne = ne->next;
	}
	return total;
}

void clean_edgelist(EDGELIST **gp) {
	if (*(gp) != NULL) {
		EDGELIST *el = *gp;
		EDGE *ep = el->start;
		EDGE *tmp = NULL;

		while (ep != NULL) {
			tmp = ep;
			ep = ep->next;
			free(tmp);
		}
		*gp = NULL;
	}
}

void display_edgelist(EDGELIST *g) {
	if (g == NULL)
		return;
	printf("\nweighted graph in edge list");
	printf("\nsize: %d", g->size);
	printf("\nformat: (from, to, weight)");
	EDGE *p = g->start;
	while (p) {
		printf("\n(%d, %d, %d)", p->from, p->to, p->weight);
		p = p->next;
	}
}
