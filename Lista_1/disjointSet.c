#include "graph.h"

int findSet(Graph *graph, int id)
{
	return graph->vertexArray[id]->parent->id;
}

void moveSet(Graph *graph, int from, int to)
{
	int fromNew = findSet(graph, from);
	int toNew = findSet(graph, to);

	for (int i = 1; i <= graph->vertexAmount; i++)
	{
		Vertex *vertex = graph->vertexArray[i];
		if (findSet(graph, vertex->id)== fromNew)
		{
			vertex->parent = graph->vertexArray[toNew];
		}
	}

}
