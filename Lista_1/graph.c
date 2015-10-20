#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"

int edge_compare(const void *a, const void *b)
{
	Edge *edge1 = ((Edge *) a);
	Edge *edge2 = ((Edge *) b);

	if (edge1->waga > edge2->waga) return 1;
	if (edge1->waga < edge2->waga) return -1;
	return 0;
}

Graph *readGraphFromFile(char *file)
{

	FILE *fp = fopen(file, "r");

	if (fp == 0)
	{
		printf("READ ERROR1\n");
		exit(1);
	}

	int iloscWierzcholkow;
	int iloscKrawedzi;

	if (fscanf(fp, "%i %i", &iloscWierzcholkow, &iloscKrawedzi) != 2)
	{
		printf("READ ERROR2\n");
		exit(1);

	}

	//Tworzymy tablice wierzchołków i krawędzi
	Edge *tablicaKrawedzi = malloc(sizeof(Edge) * iloscKrawedzi);

	if (tablicaKrawedzi == NULL)
	{
		printf("Allocation error");
		exit(1);
	}


	//Będziemy liczyć od 1
	Vertex **tablicaWierzcholkow = malloc(sizeof(Vertex) * (iloscWierzcholkow + 1));

	if (tablicaWierzcholkow == NULL)
	{
		printf("Allocation error");
		exit(1);
	}


	for (int i = 1; i < iloscWierzcholkow + 1; i++)
	{
		tablicaWierzcholkow[i] = malloc(sizeof(Vertex));
		tablicaWierzcholkow[i]->id = i;
		tablicaWierzcholkow[i]->parent =tablicaWierzcholkow[i];
		tablicaWierzcholkow[i]->zaznaczone = false;
	}

	int vertex1;
	int vertex2;
	int waga;

	int krawedz = 0;

	while (fscanf(fp, "%d %d %d", &vertex1, &vertex2, &waga) == 3)
	{

		if (krawedz >= iloscKrawedzi)
		{
			printf("Nieprawidłowa ilość krawędzi\n");
			exit(1);
		}

		tablicaKrawedzi[krawedz].vertex1 = tablicaWierzcholkow[vertex1];
		tablicaKrawedzi[krawedz].vertex2 = tablicaWierzcholkow[vertex2];
		tablicaKrawedzi[krawedz].waga = waga;
		krawedz++;
	}

	//printf("Krawedzi: %d\n", edge);

	if (krawedz != iloscKrawedzi)
	{
		printf("Nieprawidłowa ilość krawędzi\n");
		exit(1);
	}

	qsort(tablicaKrawedzi, iloscKrawedzi, sizeof(Edge), edge_compare);


	Graph *graf = malloc(sizeof(Graph));

	if (graf == NULL)
	{
		printf("Błąd alokowania pamięci\n");
		exit(1);
	}

	graf->edgeAmount = iloscKrawedzi;
	graf->vertexAmount = iloscWierzcholkow;
	graf->edgeArray = tablicaKrawedzi;
	graf->vertexArray = tablicaWierzcholkow;

	return graf;

}

