#include "header.h"
#include <stdlib.h>
#include <string.h>

//Binary search
int		searchPrice(struct s_art **arts, int n, char *name)
{
	int		mid = n / 2;
	int		left = 0;
	int		right = n - 1;

	while (left <= right)
	{
		if (!strcmp(arts[mid]->name, name))
			return (mid);
		if (strcmp(arts[mid]->name, name) < 0)
		{
			right = mid;
			mid = (left + right) / 2 + 1;
		}
		else
		{
			left = mid;
			mid = (left + right) / 2 - 1;
		}
	}
	return (-1);
}