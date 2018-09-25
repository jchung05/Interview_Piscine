#include "header.h"

char *getNot(char *a)
{
	int i = 1;
	while (i < 5)
	{
		a[i - 1] = a[i] == '0' ? '1' : '0';
		i++;
	}
	a[i] = 0;
	return a;
}

char *getAnd(char *a, char *b)
{
	int		i = 0;

	if (a[0] == '~')
		a = getNot(a);
	if (b[0] == '~')
		b = getNot(b);

	while (i < 4)
	{
		if (a[i] == '1' && a[i] == b[i])
			a[i] = '1';
		else
			a[i] = '0';
		i++;
	}
	return a;
}

char *getOr(char *a, char *b)
{
	int		i = 0;

	if (a[0] == '~')
		a = getNot(a);
	if (b[0] == '~')
		b = getNot(b);

	while (i < 4)
	{
		if (a[i] == '1' || b[i] == '1')
			a[i] = '1';
		else
			a[i] = '0';
		i++;
	}
	return a;
}

int toInt(char *bits)
{
	int result = 0;
	int i = 3;
	int shift = 1;

	while (i >= 0)
	{
		result = result + shift * (bits[i] - '0');
		shift = shift << 1;
		i--;
	}
	return result;
}