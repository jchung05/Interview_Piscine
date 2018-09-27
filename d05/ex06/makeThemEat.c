#include "header.h"

int recurse(struct s_people **people, int num, int nbTable, int totalTime, int *arr)
{
	int i = num;

	if (!people[num])
		return (1);

	for (int j = 0; j < nbTable; j++)
	{
		if (arr[j] + people[i]->time <= totalTime)
		{
			arr[j] += people[i]->time;

			if (recurse(people, num + 1, nbTable, totalTime, arr))
				return (1);
			
			arr[j] -= people[i]->time;
		}
	}
	return (0);
}


int isPossible(struct s_people **people, int nbTable, int totalTime)
{
	int result;
	int *arr;

	arr = malloc(nbTable * sizeof(int));
	result = recurse(people, 0, nbTable, totalTime, arr);

	free(arr);
	return (result);
}