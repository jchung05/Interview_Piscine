#include "header.h"

int		max(struct s_art **arr, int n, int i, int left, int right)
{
	struct s_art *tmp;
	int		root = i;

	if (left < n && strcmp(arr[left]->name, arr[root]->name) > 0)
		root = left;
	if (right < n && strcmp(arr[right]->name, arr[root]->name) > 0)
		root = right;

	return (root);
}

void	heapify(struct s_art **arr, int i, int n)
{
	struct s_art *tmp;
	while (1)
	{
		int		root = max(arr, n, i, 2 * i + 1, 2 * i + 2);

		if (root == i)
			break;

		tmp = arr[i];
		arr[i] = arr[root];
		arr[root] = tmp;
		i = root;
	}
}

void	heapSort(struct s_art **masterpiece, int n)
{
	struct s_art *tmp;
	
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(masterpiece, i, n);

	for (int i = n - 1; i >= 0; i--)
	{
		tmp = masterpiece[0];
		masterpiece[0] = masterpiece[i];
		masterpiece[i] = tmp;

		heapify(masterpiece, 0, i);
	}
}