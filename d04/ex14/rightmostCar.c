#include "header.h"

int rightmostCar(unsigned int parkingRow)
{
	int i = -1;

	while (parkingRow)
	{
		i++;
		if (parkingRow & 1)
			return (i);
		parkingRow >>= 1;
	}
	return (-1);
}