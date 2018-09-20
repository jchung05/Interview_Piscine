#include "header.h"

struct s_queue	*queueInit(void)
{
	struct s_queue	*newq;

	newq = malloc(sizeof(struct s_queue));
	if (!newq)
		return (NULL);
	newq->first = NULL;
	newq->last = NULL;
	return (newq);
}

int				isEmpty(struct s_queue *queue)
{
	return (queue->first == NULL ? 1 : 0);
}

void			enqueue(struct s_queue *queue, char *message)
{
	struct s_node	*node;

	node = malloc(sizeof(struct s_node));
	if (!node)
		return ;
	node->message = message;
	node->next = NULL;
	if (isEmpty(queue))
		queue->first = node;
	else
		queue->last->next = node;
	queue->last = node;
}

char			*dequeue(struct s_queue *queue)
{
	struct s_node	*node;
	void			*message;

	if (isEmpty(queue))
		return (NULL);
	node = queue->first;
	message = queue->first->message;
	queue->first = queue->first->next;
	free(node);
	return(message);
}

char			*peek(struct s_queue *queue)
{
	return (isEmpty(queue) == 1 ? NULL : queue->first->message);
}