#include <stdlib.h>
#include "sposobwydawania.h"

Wydawanie *wydawanie_create(int iloscMonet)
{
	Wydawanie *wydawanie = malloc(sizeof(Wydawanie));
	wydawanie->ilosc_monet = malloc(sizeof(int) * iloscMonet);

	wydawanie->wielkosc = iloscMonet;

	for (int i = 0; i < iloscMonet; i++)
	{
		wydawanie->ilosc_monet[i] = 0;
	}

	return wydawanie;

}

Wydawanie *wydawanie_clone(Wydawanie *wydawanie)
{

	Wydawanie *wydawanie1 = malloc(sizeof(Wydawanie));
	wydawanie1->wielkosc = wydawanie->wielkosc;

	wydawanie1->ilosc_monet = malloc(sizeof(int) * wydawanie->wielkosc);


	for (int i = 0; i < wydawanie1->wielkosc; i++)
	{
		wydawanie1->ilosc_monet[i] = wydawanie->ilosc_monet[i];
	}


	return wydawanie1;

}

int wydawanie_iloscMonet(Wydawanie *wydawanie)
{
	int ilosc = 0;

	for (int i = 0; i < wydawanie->wielkosc; i++)
	{
		ilosc += wydawanie->ilosc_monet[i];
	}

	return ilosc;

}

void wydawanie_free(Wydawanie *wydawanie)
{
	free(wydawanie->ilosc_monet);
	free(wydawanie);
}

