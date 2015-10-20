#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coin.h"
#include "portfel.h"
#include "sposobwydawania.h"

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

//	qsort(monety, iloscMonet, sizeof(Coin), coin_compare);

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

	if (max == doWydania)
	{
		//Wszystkie monety są użyte
		int koncowaWartosc = 0;
		for (int i = 0; i < iloscMonet; i++)
		{
			koncowaWartosc += monety[i].quantity;
		}

		printf("%d\n", koncowaWartosc);

		return 0;
	}

	portfelGlobal = malloc(sizeof(Portfel));

	portfelGlobal->ilosc_monet = iloscMonet;
	portfelGlobal->monety = monety;


	Wydawanie *sposobyWydania[doWydania + 1];

	for (int i = 0; i < doWydania + 1; i++)
	{
		sposobyWydania[i] = NULL;
	}

	Wydawanie *wydawanie = wydawanie_create(iloscMonet);

	sposobyWydania[0] = wydawanie;


	//Dla każdego nominału
	for (int i = 0; i < portfelGlobal->ilosc_monet; i++)
	{
		Coin coin = portfelGlobal->monety[i];

		//Dla każdej ilości monet
		for (int j = 0; j <= doWydania - coin.value; j++)
		{
			if (sposobyWydania[j] != NULL
				&& sposobyWydania[j]->ilosc_monet[coinValueToInt(coin.value)] < coin.quantity)
			{
				if (sposobyWydania[j + coin.value] == NULL ||
					suma(sposobyWydania[j]) + 1 < suma(sposobyWydania[j + coin.value]))
				{
					Wydawanie *wydawanie1 = wydawanie_clone(sposobyWydania[j]);
					wydawanie1->ilosc_monet[coinValueToInt(coin.value)]++;
					sposobyWydania[j + coin.value] = wydawanie1;
				}
			}
		}
	}

	if (sposobyWydania[doWydania] == NULL)
	{
		printf("%s", "NIE");
		return 0;
	}


	int test = suma(sposobyWydania[doWydania]);

	printf("%d\n", test);
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
