#include "header.h"

int toInt(char *bits)
{
	int result = 0;
	int i = 6;
	int shift = 1;

	while (--i >= 0)
	{
		result = result + shift * (bits[i] - '0');
		shift = shift << 1;
	}
	return (result);
}

char *getXor(char *a, char *b)
{
	int i = -1;

	while (++i < 6)
		a[i] = a[i] == b[i] ? '0' : '1';
	return (a);
}