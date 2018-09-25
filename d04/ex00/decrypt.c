#include "header.h"

int toInt(char *bits)
{
	int result = 0;
	int i = 5;
	int shift = 1;

	while (i >= 0)
	{
		result = result + shift * (bits[i] - '0');
		shift = shift << 1;
		i--;
	}
	return (result);
}

char *getSum(char *a, char *b)
{	
	int i = 6;
	int add = 0;

	while (--i >= 0)
	{
		if (a[i] == '0' && b[i] == '0')
		{
			a[i] = '0' + add;
			add = 0;
		}
		else if (a[i] != b[i])
			a[i] = '1' - add;
		else
		{
			a[i] = '0' + add;
			add = 1;
		}
	}
	return (a);
}