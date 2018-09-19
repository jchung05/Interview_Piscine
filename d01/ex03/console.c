#include "header.h"

struct s_stack	*stackInit(void)
{
	struct s_stack	*newstack;

	newstack = (struct s_stack *)malloc(sizeof(struct s_stack));
	if (!newstack)
		return (NULL);
	newstack->item = NULL;
	return (newstack);
}

int				pop(struct s_stack *stack)
{
	int				ret;
	struct s_item	*tmp;

	if (isEmpty(stack))
		return (-1);
	tmp = stack->item;
	ret = stack->item->idx;
	stack->item = stack->item->next;
	free(tmp);
	return (ret);
}

void			push(struct s_stack *stack, int idx)
{
	struct s_item	*node;

	node = (struct s_item *)malloc(sizeof(struct s_item));
	if (!node)
		return ;
	node->idx = idx;
	node->next = stack->item;
	stack->item = node;
}

int				isEmpty(struct s_stack *stack)
{
	return (stack->item == NULL ? 1 : 0);
}

int				peek(struct s_stack *stack)
{
	return (isEmpty(stack) == 1 ? -1 : stack->item->idx);
}

char			*console()
{
	struct s_stack	*stack = stackInit();
	static char		message[255];
	char			*input = (char *)malloc(sizeof(char) * 256);
	int				idx = 0;
	int				len = 0;
	int				peekVal = 0;

	while (1)
	{
		printf("?: ");
		fgets(input, 255, stdin);

		if (!strncmp(input, "UNDO", 4))
		{
			// peekVal = peek(stack);
			// if (peekVal != -1)
			// {
			// 	peekVal = pop(stack);
			// 	memset(message + idx, 0, 1);
			// 	idx = peekVal;
			// }
			// else
			// 	printf("There is no message to undo\n");
			if (peek(stack) != -1)
			{
				len = pop(stack);
		 		memset(message + len, '\0', 256 - len);
		 		idx = len;
		 	}
		 	else
		 		printf("There is no message to undo\n");
		}
		else if (!strncmp(input, "SEND", 4))
		{
			free(input);
			while (peek(stack))
				pop(stack);
			free(stack);
			return (message);
		}
		else
		{
			len = strlen(input);
			if (len > 1)
			{
				input[len] = 0;
				push(stack, idx);
				strncpy(&message[idx], input, len - 1);
				idx += len - 1;
				strncpy(&message[idx], " ", 1);
				idx++;
			}
		}
		printf("%s\n\n", message);
	}
	free(input);
	return (message);
}