#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "disjointSet.h"


bool wszystkieZajete(Graph *graf)
{

	int id = findSet(graf, 1);

	for (int i = 1; i <= graf->vertexAmount; i++)
	{
		if (findSet(graf, i) != id)
		{
			return false;
		}
	}

	return true;

}

int main(int argc, char *argv[])
{


	if (argc != 2)
	{
		printf("usage: %s filename", argv[0]);
		return 1;
	}

	char *file = argv[1];


	int iloscKrawedzi, iloscWierzcholkow;
	Vertex **tablicaWierzcholkow;
	Edge *tablicaKrawedzi;

	Graph *graf = readGraphFromFile(file);

	iloscKrawedzi = graf->edgeAmount;
	iloscWierzcholkow = graf->vertexAmount;
	tablicaKrawedzi = graf->edgeArray;
	tablicaWierzcholkow = graf->vertexArray;

	int krawedz = 0;
	int suma = 0;

	while (!wszystkieZajete(graf))
	{

		if (krawedz >= iloscKrawedzi)
		{
			printf("[FATAL] Graph nie jest spójny\n");
			return 1;
		}

		int id1 = tablicaKrawedzi[krawedz].vertex1->id;
		int id2 = tablicaKrawedzi[krawedz].vertex2->id;

		if (findSet(graf, id1) == findSet(graf, id2))
		{
			krawedz++;
			continue;
		}

		suma += tablicaKrawedzi[krawedz].waga;
		moveSet(graf, id1, id2);
		krawedz++;
	}


	printf("%d\n", suma);

	for (int i = 1; i < iloscWierzcholkow + 1; i++)
	{
		free(tablicaWierzcholkow[i]);
	}

	free(tablicaWierzcholkow);

	return 0;
}
