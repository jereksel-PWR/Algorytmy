#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "coin.h"
#include "list.h"
#include "portfel.h"
#include "sposobwydawania.h"

#define DEBUG false

Portfel *portfelGlobal;

int suma(Wydawanie *wydawanie);

int coinValueToInt(int value);

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

	int iloscMonet;

	if (fscanf(fp, "%d", &iloscMonet) != 1)
	{
		printf("READ ERROR\n");
		return 0;
	}


	Coin *monety = malloc(sizeof(Coin) * iloscMonet);

	int wartosc, ilosc;

	int obecneIdMonety = 0;
	int doWydania = 0;

	//Jeżeli są dwie takie same monety, dodajemy ich ilości
	while (fscanf(fp, "%d %d", &wartosc, &ilosc) == 2)
	{

		bool go = true;

		//Sprawdzanie czy moneta juz istnieje
		for (int i = 0; i < obecneIdMonety; i++)
		{
			if (monety[i].value == wartosc)
			{
				monety[i].quantity += ilosc;
				go = false;
				break;
			}
		}

		if (go)
		{
			Coin *coin = malloc(sizeof(Coin));
			coin->value = wartosc;
			coin->quantity = ilosc;

			monety[obecneIdMonety] = *coin;
			obecneIdMonety++;
		}
	}

	iloscMonet = obecneIdMonety;

	monety = realloc(monety, iloscMonet * sizeof(Coin));

//	qsort(monety, iloscMonet, sizeof(Coin), coin_compare_reverse);


	//Otwieramy plik jeszcze raz i bierzemy ostatnią liczbę
	fp = fopen(argv[1], "r");
	while (fscanf(fp, "%d", &doWydania) == 1);


	//Czy ułożenie jest w ogóle możliwe
	int max = 0;

	for (int i = 0; i < iloscMonet; i++)
	{
		max += monety[i].quantity * monety[i].value;
	}

	if (max < doWydania)
	{
		printf("NIE\n");
		return 0;
	}


	max = INT_MAX;

	portfelGlobal = malloc(sizeof(Portfel));

	portfelGlobal->ilosc_monet = iloscMonet;
	portfelGlobal->monety = monety;


	CList *sposobyWydania[doWydania + 1];


	for (int i = 0; i <= doWydania; i++)
	{
		sposobyWydania[i] = list_create();
	}

	Wydawanie *wydawanie = wydawanie_create(iloscMonet);

	list_add(sposobyWydania[0], wydawanie);


	//Dla każdego nominału
	for (int i = 0; i < portfelGlobal->ilosc_monet; i++)
	{
		Coin coin = portfelGlobal->monety[i];

		if (DEBUG)
		{
			printf("Moneta: %d/%d: %d\n", i + 1, portfelGlobal->ilosc_monet, coin.value);
		}

		//Dla każdej ilości monet
		for (int j = 0; j <= doWydania - coin.value; j++)
		{

	//		before_loop:

			//Dla każdego sposobu wydania
			for (int k = 0; k < sposobyWydania[j]->current_size; k++)
			{

				Wydawanie *wydawanie1 = list_get(sposobyWydania[j], k);

				if (wydawanie1->ilosc_monet[coinValueToInt(coin.value)] == coin.quantity)
				{
					continue;
				}

		/*		if (wydawanie_iloscMonet(wydawanie1) >= max - 1)
				{
					list_delete_id(sposobyWydania[j], k);
					goto before_loop;
				}
		*/
				Wydawanie *wydawanie2 = wydawanie_clone(wydawanie1);

				wydawanie2->ilosc_monet[coinValueToInt(coin.value)]++;

				if (wydawanie_iloscMonet(wydawanie2) >= max)
				{
					wydawanie_free(wydawanie2);
					continue;
				}

				list_add(sposobyWydania[j + coin.value], wydawanie2);

				if (j + coin.value == doWydania)
				{
					//Dostaliśmy sposób otrzymania ostatniej kwoty
					max = wydawanie_iloscMonet(wydawanie2);
				}

			}
		}
	}

	if (sposobyWydania[doWydania]->current_size == 0)
	{
		printf("%s", "NIE");
		return 0;
	}

	int min = INT_MAX;


	for (int i = 0; i < sposobyWydania[doWydania]->current_size; i++)
	{

		int test = suma(sposobyWydania[doWydania]->stuff[i]);

		if (test < min)
		{
			min = test;
		}

	}

	for (int i = 0; i <= doWydania; i++)
	{
		CList *list1 = sposobyWydania[i];
		list_clear(list1);
		free(list1->stuff);
		free(list1);
	}

	free(portfelGlobal);
	free(monety);

	printf("%d\n", min);
	return 0;
}

int coinValueToInt(int value)
{
	for (int i = 0; i < portfelGlobal->ilosc_monet; i++)
	{
		if (portfelGlobal->monety[i].value == value)
		{
			return i;
		}
	}

	return NULL;

}

int suma(Wydawanie *wydawanie)
{
	int suma = 0;

	for (int i = 0; i < wydawanie->wielkosc; i++)
	{
		suma = suma + wydawanie->ilosc_monet[i];
	}

	return suma;

}
