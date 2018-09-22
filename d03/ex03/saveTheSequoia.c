#include "header.h"
#include <stdlib.h>

void pop(struct s_node **parent, struct s_node **child)
{
	struct s_node *tmp = *parent;
	struct s_node *l = (*child)->left;
	struct s_node *r = (*child)->right;

	*parent = *child;
	if (tmp->left == *child)
	{
		(*child)->left = tmp;
		(*child)->right = tmp->right;
	}
	else
	{
		(*child)->right = tmp;
		(*child)->left = tmp->left;
	}
	tmp->left = l;
	tmp->right = r;
}

int heapify(struct s_node **node)
{
	if (!*node)
		return 0;

	int num = 1;

	if ((*node)->right && (*node)->value < (*node)->right->value)
		pop(node, &(*node)->right);
	if ((*node)->left && (*node)->value < (*node)->left->value)
		pop(node, &(*node)->left);
	num += heapify(&(*node)->right);
	num += heapify(&(*node)->left);

	return num;
}


void saveTheSequoia(struct s_node **root)
{
	if (!root)
		return;

	int n = heapify(root);

	for (int i=0;i<n-1;i++)
		heapify(root);
}