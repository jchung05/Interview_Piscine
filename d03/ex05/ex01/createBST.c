#include "header.h"
#include <stdlib.h>

struct s_node *init(int value)
{
	struct s_node *node = malloc(sizeof(struct s_node));

  if (!node)
    return (NULL);
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

struct s_node *bst(int *arr, int l, int r)
{
  if (l > r)
    return (NULL);

  int            mid = (r - l) / 2 + l;
  struct s_node *node = init(arr[mid]);

  node->left = bst(arr, l, mid - 1);
  node->right = bst(arr, mid + 1, r);
  return (node);
}

struct s_node *createBST(int *arr, int n)
{
  if (n < 1)
		return (NULL);
	return (bst(arr, 0, n - 1));
}