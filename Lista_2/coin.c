#include "coin.h"

int coin_compare(const void *a, const void *b)
{
	Coin _a = *(Coin *) a;
	Coin _b = *(Coin *) b;
	if (_a.value < _b.value) return -1;
	else if (_a.value == _b.value) return 0;
	else return 1;
}

int coin_compare_reverse(const void *a, const void *b)
{
	Coin _a = *(Coin *) a;
	Coin _b = *(Coin *) b;
	if (_a.value > _b.value) return -1;
	else if (_a.value == _b.value) return 0;
	else return 1;
}
