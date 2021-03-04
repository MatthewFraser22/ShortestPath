

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "algorithm.h"
#include "graph.h"
#include "edgelist.h"

typedef enum {
	false, true
} BOOLEAN;

EDGELIST *mst_prim(GRAPH *g, int start) {
	if (g == NULL) {
		return NULL;
	}
	BOOLEAN tree[g->order];
	int current_vertex;
	HNODE hn;
	int parent_min[g->order];
	HEAP *adjHeap = new_heap(4);
	ADJNODE *adjn = g->adjlist[start];

	int heap;
	EDGELIST *mst = new_edgelist();

	for (current_vertex = 0; current_vertex < g->order; current_vertex++) {
		tree[current_vertex] = false;
	}
	tree[start] = true;

	while (adjn != NULL) {
		hn.key = adjn->weight;
		hn.data = adjn->vertex;
		insert(adjHeap, hn);
		parent_min[adjn->vertex] = start;
		adjn = adjn->next;
	}
	while (0 < adjHeap->size) {
		hn = extract_min(adjHeap);
		current_vertex = hn.data;
		tree[current_vertex] = true;
		add_edge_end(mst, parent_min[current_vertex], current_vertex, hn.key);
		adjn = g->adjlist[current_vertex];

		while (adjn != NULL) {
			if (tree[adjn->vertex] == false) {
				heap = find_index(adjHeap, adjn->vertex);
				if (0 <= heap && adjn->weight < (adjHeap->hnap + heap)->key) {
					decrease_key(adjHeap, heap, adjn->weight);
					parent_min[adjn->vertex] = current_vertex;
				} else if (heap == -1) {
					hn.key = adjn->weight;
					hn.data = adjn->vertex;
					insert(adjHeap, hn);
					parent_min[adjn->vertex] = current_vertex;
				}
			}
			adjn = adjn->next;
		}
	}
	return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {

	if (g == NULL) {
		return NULL;
	}

	int parent_min[g->order];
	int weight_short[g->order];
	int current_vertex;
	HNODE hn;
	HEAP *adjHeap = new_heap(4);
	BOOLEAN tree[g->order];
	EDGELIST *spt = new_edgelist();
	ADJNODE *adjn = g->adjlist[start];
	int heap;


	for (current_vertex = 0; current_vertex < g->order; current_vertex++) {
		tree[current_vertex] = false;
		weight_short[current_vertex] = 9999;
	}
	tree[start] = true;
	weight_short[start] = 0;

	while (adjn != NULL) {
		hn.key = adjn->weight + weight_short[start];
		hn.data = adjn->vertex;
		insert(adjHeap, hn);
		parent_min[adjn->vertex] = start;
		adjn = adjn->next;
	}

	while (0 < adjHeap->size) {

		hn = extract_min(adjHeap);
		current_vertex = hn.data;
		tree[current_vertex] = true;
		weight_short[current_vertex] = hn.key;
		add_edge_end(spt, parent_min[current_vertex], current_vertex,
				weight_short[current_vertex]
						- weight_short[parent_min[current_vertex]]);

		adjn = g->adjlist[current_vertex];
		while (adjn != NULL) {

			if (tree[adjn->vertex] == false) {

				heap = find_index(adjHeap, adjn->vertex);

				if (0 <= heap
						&& adjn->weight + weight_short[current_vertex]
								< (adjHeap->hnap + heap)->key) {
					decrease_key(adjHeap, heap,
							adjn->weight + weight_short[current_vertex]);
					parent_min[adjn->vertex] = current_vertex;

				} else if (heap == -1) {
					hn.key = adjn->weight + weight_short[current_vertex];
					hn.data = adjn->vertex;
					insert(adjHeap, hn);
					parent_min[adjn->vertex] = current_vertex;
				}
			}
			adjn = adjn->next;
		}
	}

	return spt;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
	if (g == NULL) {
		return NULL;
	}

	ADJNODE *adjn = g->adjlist[start];
	int weight_short[g->order];
	int current_vertex;
	int heap;
	HEAP *adjHeap = new_heap(4);
	BOOLEAN tree[g->order];
	HNODE hn;


	int min_parent[g->order];
	EDGELIST *sp = new_edgelist();

	for (current_vertex = 0; current_vertex < g->order; current_vertex++) {
		tree[current_vertex] = false;
		weight_short[current_vertex] = 9999;
	}
	tree[start] = true;
	weight_short[start] = 0;

	while (adjn != NULL) {
		hn.key = adjn->weight + weight_short[start];
		hn.data = adjn->vertex;
		insert(adjHeap, hn);
		min_parent[adjn->vertex] = start;
		adjn = adjn->next;
	}

	while (0 < adjHeap->size) {

		hn = extract_min(adjHeap);
		current_vertex = hn.data;
		tree[current_vertex] = true;
		weight_short[current_vertex] = hn.key;

		if (current_vertex == end) {
			break;
		}
		adjn = g->adjlist[current_vertex];
		while (adjn != NULL) {
			if (tree[adjn->vertex] == false) {
				heap = find_index(adjHeap, adjn->vertex);
				if (0 <= heap
						&& adjn->weight + weight_short[current_vertex]
								< (adjHeap->hnap + heap)->key) {
					decrease_key(adjHeap, heap,
							adjn->weight + weight_short[current_vertex]);
					min_parent[adjn->vertex] = current_vertex;

				} else if (heap == -1) {
					hn.key = adjn->weight + weight_short[current_vertex];
					hn.data = adjn->vertex;
					insert(adjHeap, hn);
					min_parent[adjn->vertex] = current_vertex;
				}
			}
			adjn = adjn->next;
		}
	}
	current_vertex = end;
	while (1) {
		if (current_vertex == start) {
			break;
		}
		add_edge_start(sp, min_parent[current_vertex], current_vertex,
				weight_short[current_vertex]
						- weight_short[min_parent[current_vertex]]);
		current_vertex = min_parent[current_vertex];
	}

	return sp;
}
