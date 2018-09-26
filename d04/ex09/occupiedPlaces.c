#include "header.h"

//Kernighan's algorithm
int		occupiedPlaces(unsigned int parkingRow)
{
    unsigned int count = 0;
    while (parkingRow)
    {
      parkingRow &= (parkingRow - 1);
      count++;
    }
    return (count);
}