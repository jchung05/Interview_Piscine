#include "header.h"

struct s_node	*clone_random(struct s_node *orig, struct s_node *copy)
{
	struct s_node	*itr1;
	struct s_node	*itr2;
	struct s_node	*citr1;
	struct s_node	*citr2;
	
	itr1 = orig;
	citr1 = copy;
	while (itr1)
	{
		if (itr1->random)
		{
			itr2 = orig;
			citr2 = copy;
			while (itr2 != itr1->random)
			{
				itr2 = itr2->next;
				citr2 = citr2->next;
			}
			citr1->random = citr2;
		}
		else
			citr1->random = (struct s_node *)0;
		itr1 = itr1->next;
		citr1 = citr1->next;
	}
	return (copy);
}

struct s_node	*cloneGameBoard(struct s_node *node)
{
	struct s_node	*head;
	struct s_node	*newitr;
	struct s_node	*tmp;
	struct s_node	*itr;

	if (!node)
		return ((struct s_node *)0);
	itr = node;
	if (itr)
	{
		newitr = malloc(sizeof(struct s_node));
		newitr->value = itr->value;
		newitr->next = ((struct s_node *)0);
		newitr->random = ((struct s_node *)0);
		itr = itr->next;
		head = newitr;
	}
	while (itr)
	{
		tmp = malloc(sizeof(struct s_node));
		tmp->value = itr->value;
		tmp->next = ((struct s_node *)0);
		tmp->random = ((struct s_node *)0);
		newitr->next = tmp;
		newitr = tmp;
		itr = itr->next;
	}
	head = clone_random(node, head);
	return (head);
}