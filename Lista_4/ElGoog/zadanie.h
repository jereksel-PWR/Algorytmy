#ifndef ZADANIE_H_INCLUDED
#define ZADANIE_H_INCLUDED

typedef struct zadanie Zadanie;

typedef struct zadanie
{
	int superkomputerCzas;
	int komputerCzas;
} ZADANIE;


int zadanie_compare(const void *a, const void *b);


#endif //ZADANIE_5_ZADANIE_H
