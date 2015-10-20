#include "graf.h"

int wierzcholek_compare(const void *a, const void *b)
{
	Wierzcholek wierzcholek1 = *((Wierzcholek *) a);
	Wierzcholek wierzcholek2 = *((Wierzcholek *) b);

	if (wierzcholek1.id > wierzcholek2.id) return 1;
	if (wierzcholek1.id < wierzcholek2.id) return -1;
	return 0;
}

int krawedz_compare(const void *a, const void *b)
{
	Krawedz krawedz1 = *((Krawedz *) a);
	Krawedz krawedz2 = *((Krawedz *) b);

	return wierzcholek_compare(krawedz1.wierzcholek1, krawedz2.wierzcholek1);

}