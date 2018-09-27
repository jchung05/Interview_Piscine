#include "header.h"

double	max = 0.0;

void getMax(int pizzaSize, double *prices, double temp)
{
	if (!pizzaSize && temp > max)
		max = temp;

	for (int i = 1; i <= pizzaSize; i++)
		getMax(pizzaSize - i, prices, temp + prices[i]);

	return ;
}

double bestPrice(int pizzaSize, double *prices)
{
	getMax(pizzaSize, prices, 0);
	return (max);
}