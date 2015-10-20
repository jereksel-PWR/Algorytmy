#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdbool.h>

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;

typedef struct graph
{
	int vertexAmount;
	int edgeAmount;
	Vertex **vertexArray;
	Edge *edgeArray;
} GRAPH;


struct vertex
{
	int id;
	Vertex *parent;  //kruskal
	bool zaznaczone; //prim
} VERTEX;


struct edge
{
	Vertex *vertex1;
	Vertex *vertex2;
	int waga;
} EDGE;


int edge_compare(const void *a, const void *b);
Graph *readGraphFromFile(char *file);
#endif
