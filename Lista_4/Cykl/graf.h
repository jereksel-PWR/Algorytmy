#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED

#define bialy 0
#define szary 1
#define czarny 2


typedef struct krawedz Krawedz;
typedef struct wierzcholek Wierzcholek;

typedef struct krawedz
{
	Wierzcholek* wierzcholek1;
	Wierzcholek* wierzcholek2;
} KRAWEDZ;

typedef struct wierzcholek
{
	int id;
	int kolor;
	int krawedzStart;
} WIERZCHOLEK;


int wierzcholek_compare(const void *a, const void *b);

int krawedz_compare(const void *a, const void *b);

#endif