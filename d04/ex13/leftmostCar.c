#include "header.h"

int			leftmostCar(unsigned int parkingRow)
{
	int		i = -1;

	while (parkingRow)
	{
		i++;
		parkingRow >>= 1;
	}

	return (i);
}