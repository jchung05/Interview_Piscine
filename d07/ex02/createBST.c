#include "header.h"
#include <stdlib.h>

struct s_node *createNode(int value)
{
	struct s_node	*node;

	node = malloc(sizeof(struct s_node));
	if (!node)
		return (NULL);

	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

struct s_node *insertNode(int *arr, int left, int right)
{
	struct s_node	*node;
	int				mid;

	if (left > right)
		return (NULL);

	mid = left + (right - left) / 2;
	node = createNode(arr[mid]);
	node->left = insertNode(arr, left, mid - 1);
	node->right = insertNode(arr, mid + 1, right);
	return (node);
}

struct s_node *createBST(int *arr, int n)
{
	if (n <= 0)
		return (NULL);

	return (insertNode(arr, 0, n - 1));
}