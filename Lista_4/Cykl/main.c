#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "graf.h"

#define stos

typedef struct wierzcholekHolder WierzcholekHolder;

typedef struct wierzcholekHolder
{
	Wierzcholek *wierzcholek;
	bool doZmiany;
} wierzcholekHolder;


void szukajCyklu(Wierzcholek *wierzcholek, Krawedz **krawedzie, int iloscKrawedzi)
{

	if (wierzcholek->kolor == czarny || wierzcholek->krawedzStart == -1)
	{
		return;
	}

	wierzcholek->kolor = szary;

	for (int i = wierzcholek->krawedzStart; i < iloscKrawedzi && krawedzie[i]->wierzcholek1 == wierzcholek; i++)
	{

		switch (krawedzie[i]->wierzcholek2->kolor)
		{

			case bialy:
				szukajCyklu(krawedzie[i]->wierzcholek2, krawedzie, iloscKrawedzi);
				break;
			case szary:
				printf("TAK");
				exit(0);
				break;
			case czarny:
				break;
			default:
				break;
		}

	}


	wierzcholek->kolor = czarny;

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

	int iloscWierzcholkow;
	int iloscKrawedzi;

	fscanf(fp, "%d", &iloscWierzcholkow);
	fscanf(fp, "%d", &iloscKrawedzi);

	iloscWierzcholkow++;

	Wierzcholek **wierzcholki = malloc((iloscWierzcholkow) * sizeof(Wierzcholek *));
	Krawedz **krawedzie = malloc((iloscKrawedzi) * sizeof(Krawedz *));


	for (int i = 0; i < iloscWierzcholkow; i++)
	{
		Wierzcholek *wierzcholek = malloc(sizeof(Wierzcholek));
		wierzcholek->id = i;
		wierzcholek->kolor = bialy;
		wierzcholek->krawedzStart = -1;
		wierzcholki[i] = wierzcholek;
	}


	for (int i = 0; i < iloscKrawedzi; i++)
	{
		int wierzcholek1;
		int wierzcholek2;
		Krawedz *krawedz = malloc(sizeof(Krawedz));

		fscanf(fp, "%d", &wierzcholek1);
		fscanf(fp, "%d", &wierzcholek2);

		krawedz->wierzcholek1 = wierzcholki[wierzcholek1];
		krawedz->wierzcholek2 = wierzcholki[wierzcholek2];

		krawedzie[i] = krawedz;

	}

	qsort(krawedzie, iloscKrawedzi, sizeof(Krawedz *), krawedz_compare);

	krawedzie[0]->wierzcholek1->krawedzStart = 0;

	for (int i = 0; i < iloscKrawedzi - 1; i++)
	{
		if (krawedzie[i]->wierzcholek1->id != krawedzie[i + 1]->wierzcholek1->id)
		{
			krawedzie[i + 1]->wierzcholek1->krawedzStart = i + 1;
		}
	}

#ifdef stos

	Stack *stack = stack_create();

	for (int i = 0; i < iloscWierzcholkow; i++)
	{

		Wierzcholek *wierzcholek = wierzcholki[i];

		if (wierzcholek->krawedzStart == -1)
		{
			wierzcholek->kolor = czarny;
		}

	}


	for (int i = 0; i < iloscWierzcholkow; i++)
	{

		Wierzcholek *wierzcholek = wierzcholki[i];

		if (wierzcholek->kolor == czarny)
		{
			continue;
		}

		WierzcholekHolder *holder = malloc(sizeof(WierzcholekHolder));

		holder->wierzcholek = wierzcholek;
		holder->doZmiany = false;

		stack_push(stack, holder);

		while (!stack_empty(stack))
		{
			holder = stack_pop(stack);

			if (holder->doZmiany)
			{
				holder->wierzcholek->kolor = czarny;
			}

			if (holder->wierzcholek->kolor == szary)
			{
				printf("TAK");
				exit(1);
			}

			if (holder->wierzcholek->kolor == czarny)
			{
				continue;
			}

			holder->wierzcholek->kolor = szary;
			holder->doZmiany = true;
			stack_push(stack, holder);

			for (int j = wierzcholek->krawedzStart; j < iloscKrawedzi && krawedzie[j]->wierzcholek1 == wierzcholek; i++)
			{
				wierzcholek = krawedzie[j]->wierzcholek2;

				if (wierzcholek->kolor == szary)
				{
					printf("TAK");
					exit(0);
				}

				if (wierzcholek->kolor == czarny)
				{
					continue;
				}


				holder = malloc(sizeof(WierzcholekHolder));

				holder->wierzcholek = wierzcholek;
				holder->doZmiany = false;

				stack_push(stack, holder);
			}


		}

	}


#else

	for (int i = 0; i < iloscKrawedzi; i++)
	{
		szukajCyklu(krawedzie[i]->wierzcholek1, krawedzie, iloscKrawedzi);
	}

#endif

	printf("NIE");


	return 0;
}