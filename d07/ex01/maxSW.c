#include "header.h"

struct s_deque	*dequeInit(void)
{
	struct s_deque *deque;

	deque = malloc(sizeof(struct s_deque));
	if (!deque)
		return (NULL);
	deque->first = NULL;
	deque->last = NULL;
	return (deque);
}

void			pushFront(struct s_deque *deque, int value)
{
	if (!deque)
		return ;

	struct s_dequeNode *node;

	node = malloc(sizeof(struct s_dequeNode));
	if (!node)
		return ;

	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	if (!deque->first)
	{
		deque->first = node;
		deque->last = node;
	}
	else
	{
		node->next = deque->first;
		deque->first->prev = node;
		deque->first = node;
	}
}

void			pushBack(struct s_deque *deque, int value)
{
	if (!deque)
		return ;

	struct s_dequeNode *node;

	node = malloc(sizeof(struct s_dequeNode));
	if (!node)
		return ;

	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	if (!deque->last)
	{
		deque->first = node;
		deque->last = node;
	}
	else
	{
		node->prev = deque->last;
		deque->last->next = node;
		deque->last = node;
	}
}

int				popFront(struct s_deque *deque)
{
	struct s_dequeNode	*node;
	int					value;

	if (!deque || !deque->first)
		return (INT_MIN);

	node = deque->first;
	value = deque->first->value;
	deque->first = deque->first->next;

	if (!deque->first)
		deque->last = NULL;
	else
		deque->first->prev = NULL;
	free(node);
	return (value);
}

int				popBack(struct s_deque *deque)
{
	struct s_dequeNode	*node;
	int					value;

	if (!deque || !deque->last)
		return (INT_MIN);

	node = deque->last;
	value = deque->last->value;
	deque->last = deque->last->prev;

	if (!deque->last)
		deque->first = NULL;
	else
		deque->last->next = NULL;
	free(node);
	return (value);
}

int				peekBack(struct s_deque *deque)
{
	if (!deque || !deque->last)
		return (INT_MIN);
	return (deque->last->value);
}

int				peekFront(struct s_deque *deque)
{
	if (!deque || !deque->first)
		return (INT_MIN);
	return (deque->first->value);
}

struct s_max *maxSlidingWindow(int *arr, int n, int k)
{
	if (k > n || k < 0)
		return (NULL);

	struct s_deque *deque = dequeInit();
	struct s_max *result = malloc(sizeof(struct s_max));
	result->max = malloc(sizeof(int) * (n - k + 1));
	result->length = n - k + 1;

	int		i;

	for (i = 0; i < k; i++)
	{
		while (peekBack(deque) != INT_MIN && arr[i] >= arr[peekBack(deque)])
			popBack(deque);
		pushBack(deque, i);
	}

	for (i = k; i < n; i++)
	{
		result->max[i - k] = arr[peekFront(deque)];
		while (peekFront(deque) != INT_MIN && peekFront(deque) <= i - k)
			popFront(deque);
		while (peekBack(deque) != INT_MIN && arr[i] >= arr[peekBack(deque)])
			popBack(deque);
		pushBack(deque, i);
	}
	result->max[i - k] = arr[peekFront(deque)];

	return (result);
}