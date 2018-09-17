#include "header.h"
#include <stdlib.h>
#include <string.h>

int		comparator(const void *a, const void *b)
{
	return strcmp((const char *)(((struct s_art *)a)->name), (const char *)(((struct s_art *)b)->name));
}

void	sortArts(struct s_art **arts)
{
	int		i = -1;

	while (arts[++i])
		;
	qsort(arts, i, sizeof(struct s_art *), &comparator);
}