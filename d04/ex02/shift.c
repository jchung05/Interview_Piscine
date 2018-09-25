#include "header.h"

int toInt(char *bits)
{
	int result = 0;
	int i = 6;
	int shift = 1;
	int neg = (bits[0] == '1') ? 1 : 0;

	while (--i >= 1)
	{
		result = result + shift * ((bits[i] == '1') ^ neg);
		shift = shift << 1;
	}
	return (neg ? -result - 1 : result);
}

char *rightShift(char *bin, int k)
{
	int i = 6;

	if (k < 6)
		while (--i - k >= 0)
			bin[i] = bin[i - k];

	i = -1;
	while (++i < k && i < 6)
	 	bin[i] = '1';

	return (bin);
}

char *leftShift(char *bin, int k)
{
	int i = -1;

	if (k < 6)
		while (++i + k < 6)
			bin[i] = bin[i + k];

	i = 5;
	while (i >= 0 && k > 0)
	{
	 	bin[i] = '0';
	 	i--;
	 	k--;
	}
	return (bin);
}