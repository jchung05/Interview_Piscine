#include "header.h"

void swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void permute(char *str, int start, int end)
{
	if (start == end)
	{
		printf("%s\n", str);
		return ;
	}

	for (int i = start; i <= end; i++)
	{
		swap(&str[start], &str[i]);
		permute(str, start + 1, end);
		swap(&str[i], &str[start]);
	}
}

void printPermutations(char *str)
{
	if (str)
		permute(str, 0, strlen(str) - 1);
}