#ifndef WYDAWANIE_H_INCLUDED
#define WYDAWANIE_H_INCLUDED

typedef struct wydawanie Wydawanie;

typedef struct wydawanie
{
	int *ilosc_monet;
	int wielkosc;
} WYDAWANIE;


Wydawanie *wydawanie_create(int iloscMonet);

Wydawanie *wydawanie_clone(Wydawanie *wydawanie);

int wydawanie_iloscMonet(Wydawanie *wydawanie);

void wydawanie_free(Wydawanie *wydawanie);

#endif
