#include <stdio.h>
#include <stdlib.h>

int *tab;
int *t;

int liczbaInwersji = 0;

void merge(int pocz, int sr, int kon)
{
	int i, j, q;
	for (i = pocz; i <= kon; i++) t[i] = tab[i];
	i = pocz;
	j = sr + 1;
	q = pocz;

	for (int a = pocz; a <= sr; a++)
	{
		for (int b = kon; b >= sr + 1; b--)
		{
			if (tab[a] > 2 * tab[b])
			{
				liczbaInwersji += b - (sr);
				break;
			}
		}
	}


	while (i <= sr && j <= kon)
	{
		if (t[i] < t[j])
		{
			tab[q] = t[i];
			q++;
			i++;
		}
		else
		{
			tab[q] = t[j];
			q++;
			j++;
		}
	}

	while (i <= sr)
		tab[q++] = t[i++];

	while (j <= kon)
		tab[q++] = t[j++];

}

void mergesort(int pocz, int kon)
{
	int sr;
	if (pocz < kon)
	{
		sr = (pocz + kon) / 2;
		mergesort(pocz, sr);
		mergesort(sr + 1, kon);
		merge(pocz, sr, kon);
	}
}

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

	int size;

	fscanf(fp, "%d", &size);

	tab = malloc(size * sizeof(int));
	t = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
	{
		int temp;
		fscanf(fp, "%d", &temp);
		tab[i] = temp;
	}

	mergesort(0, size - 1);

	printf("%d\n", liczbaInwersji);

	return 0;
}