#include "header.h"

int			carPosition(unsigned int parkingRow)
{
	int		ret;

	ret = -1;
	if (!parkingRow && !(parkingRow & (parkingRow - 1)))
		for (ret = 0; parkingRow > 1; ret++)
			parkingRow >>= 1;
	return (ret);
}