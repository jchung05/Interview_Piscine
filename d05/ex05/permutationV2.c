#include "header.h"

void swap(char *a, char *b)
{
	char tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void permute(char *arr, int start, int end, struct s_dict *dict)
{
	if (start == end && dictSearch(dict, arr) == -1)
		printf("%s\n", arr);
	if (start == end)
		dictInsert(dict, arr, 1);

	for (int i = start; i < end; i++)
	{
		swap(&arr[i], &arr[start]);
		permute(arr, start + 1, end, dict);
		swap(&arr[i], &arr[start]);
	}
}

void printUniquePermutations(char *str)
{
	if (!str)
		return ;
	permute(str, 0, strlen(str), dictInit(1000));
}