#include "header.h"
#include <stdlib.h>
#include <string.h>

//Binary search
int		searchPrice(struct s_art **arts, int n, char *name)
{
	int		mid;
	int		left = 0;
	int		right = n - 1;

	while (left <= right)
	{
		mid = (right - left) / 2;

		if (!strcmp(arts[mid]->name, name))
			return (mid);
		if (strcmp(arts[mid]->name, name) < 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}