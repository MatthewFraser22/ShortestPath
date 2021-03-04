

#include <stdio.h>
#include "graph.h"
#include "edgelist.h"
#include "algorithm.h"

int main(){
  //create a weighted graph
  GRAPH *g = new_graph(5);
  add_edge(g, 0, 1, 7);
  add_edge(g, 1, 0, 7);
  add_edge(g, 0, 2, 3);
  add_edge(g, 2, 0, 3);
  add_edge(g, 1, 2, 4);
  add_edge(g, 2, 1, 4);
  add_edge(g, 2, 3, 10);
  add_edge(g, 3, 2, 10);
  add_edge(g, 1, 3, 9);
  add_edge(g, 3, 1, 9);
  add_edge(g, 1, 4, 11);
  add_edge(g, 4, 1, 11);
  display_graph(g);

  //compute MST by Prim's algorithm using min-heap
  EDGELIST *t = mst_prim(g, 0);
  printf("\n\nMST by Prim's algorithm");
  display_edgelist(t);
  printf("\nweight: %d", weight_edgelist(t));
  clean_edgelist(&t);
  printf("\nMST is deleted");

  //compute SPT by Dijsktra's algorithm using min-heap
	t = spt_dijkstra(g, 0);
  printf("\n\nSPT by Dijsktra's algorithm");
  display_edgelist(t);
  clean_edgelist(&t);
  printf("\nSPT is deleted");

  //compute SP by Dijsktra's algorithm using min-heap
  int start = 0, end = 4;
	t = sp_dijkstra(g, start, end);
  printf("\n\nShortest path from %d to %d", start, end);
  display_edgelist(t);
	printf("\nThe length of the shortest path: %d", weight_edgelist(t));
  clean_edgelist(&t);
  printf("\nSP is deleted");

  clean_graph(&g);
  printf("\n\ngraph is deleted");
  return 0;
}

/*
gcc heap.c graph.c edgelist.c algorithm.c a10q3.c -o a10q3
a10q3

weighted graph in adjacency list
order: 5
size: 12
node from: (to weight)
node 0: (1, 7) (2, 3)
node 1: (0, 7) (2, 4) (3, 9) (4, 11)
node 2: (0, 3) (1, 4) (3, 10)
node 3: (2, 10) (1, 9)
node 4: (1, 11)

MST by Prim's algorithm
weighted graph in edge list
size: 4
format: (from, to, weight)
(0, 2, 3)
(2, 1, 4)
(1, 3, 9)
(1, 4, 11)
weight: 27
MST is deleted

SPT by Dijsktra's algorithm
weighted graph in edge list
size: 4
format: (from, to, weight)
(0, 2, 3)
(0, 1, 7)
(2, 3, 10)
(1, 4, 11)
SPT is deleted

Shortest path from 0 to 4
weighted graph in edge list
size: 2
format: (from, to, weight)
(0, 1, 7)
(1, 4, 11)
The length of the shortest path: 18
SP is deleted

graph is deleted
*/
