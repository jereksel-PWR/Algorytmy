#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "graph.h"

#define FASTER

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("usage: %s filename", argv[0]);
		return 1;
	}

	char *file = argv[1];


	int iloscWierzcholkow;
	int iloscKrawedzi;
	Edge *tablicaKrawedzi;
	Vertex **tablicaWierzcholkow;


	int suma = 0;

	Graph *graf = readGraphFromFile(file);

	iloscKrawedzi = graf->edgeAmount;
	iloscWierzcholkow = graf->vertexAmount;
	tablicaKrawedzi = graf->edgeArray;
	tablicaWierzcholkow = graf->vertexArray;


	Heap *kopiec = malloc(sizeof(Heap));
	kopiec->size = 0;
	kopiec->array = malloc(sizeof(int) * iloscWierzcholkow);


#ifndef FASTER
	//Pierwszy wierzchołek
	heap->size = 1;
	heap->array[0] = 1;


	while (heap->size != vertexAmount)
	{
		for (int i = 0; i < edgeAmount; i++)
		{

			bool find1 = find(heap, edgeArray[i].vertex1->id);
			bool find2 = find(heap, edgeArray[i].vertex2->id);
			if (find1 ^ find2)
			{
				if (find1)
				{
					add(heap, edgeArray[i].vertex2->id);
				}
				else
				{
					add(heap, edgeArray[i].vertex1->id);
				}

				suma += edgeArray[i].waga;
				break;
			}

			if (i == edgeAmount - 1)
			{
				printf("[FATAL] Graph nie jest spójny\n");
				return 1;
			}

		}
	}


#else

	//Pierwszy wierzchołek
	kopiec->size = 1;
	tablicaWierzcholkow[1]->zaznaczone = true;


	while (kopiec->size != iloscWierzcholkow)
	{
		for (int i = 0; i < iloscKrawedzi; i++)
		{

			bool find1 = tablicaKrawedzi[i].vertex1->zaznaczone;
			bool find2 = tablicaKrawedzi[i].vertex2->zaznaczone;

			if (find1 ^ find2)
			{

				tablicaKrawedzi[i].vertex1->zaznaczone = true;
				tablicaKrawedzi[i].vertex2->zaznaczone = true;

				suma += tablicaKrawedzi[i].waga;
				kopiec->size++;
				break;

			}

			if (i == iloscKrawedzi - 1)
			{
				printf("[FATAL] Graph nie jest spójny\n");
				return 1;
			}

		}
	}


#endif


	printf("%d\n", suma);


	for (int i = 0; i < iloscWierzcholkow + 1; i++)
	{
		free(tablicaWierzcholkow[i]);
	}

	free(tablicaWierzcholkow);

	return 0;
}
