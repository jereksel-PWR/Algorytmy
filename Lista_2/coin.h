#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

typedef struct coin Coin;

typedef struct coin
{
	int value;
	int quantity;
} COIN;

int coin_compare(const void *a, const void *b);
int coin_compare_reverse(const void *a, const void *b);

#endif
