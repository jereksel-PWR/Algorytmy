#include <stdio.h>
#include <stdlib.h>
#include "zadanie.h"

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		return -1;
	}


	FILE *fp = fopen(argv[1], "r");

	if (fp == 0)
	{
		printf("READ ERROR\n");
		return 0;
	}


	Zadanie *tab;
	unsigned int size;

	fscanf(fp, "%d", &size);

	tab = malloc(size * sizeof(Zadanie));
	int *czasy = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		Zadanie *zadanie = malloc(sizeof(Zadanie));
		fscanf(fp, "%d", &zadanie->superkomputerCzas);
		fscanf(fp, "%d", &zadanie->komputerCzas);

		tab[i] = *zadanie;
	}

	qsort(tab, size, sizeof(Zadanie), zadanie_compare);

	int czasTemp = 0;

	for (int i = 0; i < size; i++)
	{
		int superkomputerCzas = tab[i].superkomputerCzas;
		int komputerCzas = tab[i].komputerCzas;

		czasy[i] = czasTemp + superkomputerCzas + komputerCzas;

		czasTemp += superkomputerCzas;
	}


	int max = 0;

	for (int i = size - 1; i >= 0; i--)
	{
		if (czasy[i] > max)
		{
			max = czasy[i];
		}

	}

	printf("%d\n", max);

	return 0;
}
