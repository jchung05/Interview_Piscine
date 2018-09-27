#include "header.h"

void	recurse(struct s_array *arr, int pizzaSize)
{
	if (!pizzaSize && arr->sum)
		arrayPrint(arr);
	if (!pizzaSize)
		return ;

	struct s_array	*tmp;

	for (int i = 1; i <= pizzaSize; i++)
	{
		tmp = arrayClone(arr);
		arrayAppend(tmp, i);
		recurse(tmp, pizzaSize - i);
	}
}

void	printPossibleSlices(int pizzaSize)
{
	recurse(arrayInit(), pizzaSize);
}