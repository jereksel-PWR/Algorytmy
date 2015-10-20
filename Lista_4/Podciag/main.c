#include <stdio.h>
#include <stdlib.h>

int binarysearch(int *array, int N, int szukana)
{

	int poczatek = 0;
	int koniec = N;
	int srodek;

	while (koniec != poczatek)
	{

		srodek = (koniec + poczatek) / 2;

		if (szukana >= array[srodek])
		{
			poczatek = srodek + 1;
		}
		else if (szukana < array[srodek])
		{
			koniec = srodek;
		}
	}


	while (!(array[koniec] >= szukana && array[koniec - 1] < szukana))
	{
		koniec--;
	}

	if (koniec < 0) {
		koniec = 0;
	}

	return koniec;
}

int podciag(int *A, int N)
{
	int *array = malloc(sizeof(int) * (N + 1));
	int current = 0;
	array[0] = A[0];

	for (int i = 1; i < N; i++)
	{

		if (A[i] <= array[0])
		{
			array[0] = A[i];
		}
		else if (A[i] > array[current])
		{
			current++;
			array[current] = A[i];
		}
		else if (A[i] < array[current])
		{
			int temp = binarysearch(array, current, A[i]);

			array[temp] = A[i];
		}


	}

	return current+1;
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == 0)
	{
		printf("READ ERROR\n");
		return 0;
	}

	int *tab;

	int size;

	fscanf(fp, "%d", &size);

	tab = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		int temp;
		fscanf(fp, "%d", &temp);
		tab[i] = temp;
	}

	int wynik = podciag(tab, size);

	printf("%d\n", wynik);

	return 0;
}