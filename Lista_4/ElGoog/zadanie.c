#include "zadanie.h"

int zadanie_compare(const void *a, const void *b)
{
	Zadanie zadanie1 = *((Zadanie *) a);
	Zadanie zadanie2 = *((Zadanie *) b);

	if (zadanie1.komputerCzas < zadanie2.komputerCzas) return 1;
	if (zadanie1.komputerCzas > zadanie2.komputerCzas) return -1;
	return 0;
}
