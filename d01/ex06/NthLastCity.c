#include "header.h"

char			*NthLastCity(struct s_city *city, int n)
{
	struct s_city	*tmp = city;
	struct s_city	*tmp2 = city;

	while (n-- > 0 && tmp2)
		tmp2 = tmp2->next;

	while (tmp2->next)
	{
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}

	return (tmp->name);
}