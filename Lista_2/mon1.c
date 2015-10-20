#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY INT_MAX

int my_compare(const void *a, const void *b)
{
	int _a = *(int *) a;
	int _b = *(int *) b;
	if (_a < _b) return -1;
	else if (_a == _b) return 0;
	else return 1;
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		return 0;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == 0)
	{
		printf("READ ERROR\n");
		return 0;
	}

	unsigned int iloscMonet;

	if (fscanf(fp, "%u", &iloscMonet) != 1)
	{
		printf("READ ERROR\n");
		return 0;

	}

	int monety[iloscMonet];

	int moneta;

	int obecneIdMonety = 0;
	int doWydania = 0;

	while (fscanf(fp, "%d", &moneta) == 1)
	{

		if (obecneIdMonety == iloscMonet)
		{
			doWydania = moneta;
			break;
		}

		monety[obecneIdMonety] = moneta;
		obecneIdMonety++;

	}

	//qsort(monety, iloscMonet, sizeof(int), my_compare);

	int temp[doWydania + 1];

	temp[0] = 0;

	for (int i = 1; i <= doWydania; i++)
	{
		temp[i] = INFINITY;
	}


	for (int i = 0; i < iloscMonet; i++)
	{
		int n = monety[i];
		for (int j = 0; j <= doWydania - n; j++)
			if (temp[j] < INFINITY)
			{
				if (temp[j] + 1 < temp[j + n])
				{
					temp[j + n] = temp[j] + 1;
				}
			}
	}


	if (temp[doWydania] == INFINITY)
	{
		printf("%s\n", "NIE");
	}
	else
	{
		printf("%d\n", temp[doWydania]);
	}


	return 0;
}