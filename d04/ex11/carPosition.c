#include "header.h"

int carPosition(unsigned int parkingRow)
{
	int i = 0;
	int found = 0;

	while (parkingRow)
	{
		if (parkingRow & 1)
			found++;
		i++;
		parkingRow = parkingRow / 2;
	}
	if (!i || found != 1)
		return (-1);
	return (i - 1);
}