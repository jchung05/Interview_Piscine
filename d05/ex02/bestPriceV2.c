#include "header.h"
#include <stdlib.h>
#include <string.h>

double recurse(int size, double *prices, double *bestPrices)
{
	if (!bestPrices[size])
	{
		double	tmp;

		bestPrices[size] = prices[size];
		for (int i = 1; i <= size / 2; i += 2)
		{
			tmp = recurse(i, prices, bestPrices) + recurse(size - i, prices, bestPrices);
			bestPrices[size] = (tmp > bestPrices[size]) ? tmp : bestPrices[size];
		}
	}
	return (bestPrices[size]);
}

double optimizedBestPrice(int pizzaSize, double *prices)
{
	double value;
	double *bestPrices = malloc((pizzaSize + 1) * sizeof(double));

	memset(bestPrices, 0, pizzaSize + 1);

	value = recurse(pizzaSize, prices, bestPrices);

	free(bestPrices);
	return value;
}