#include "header.h"

struct s_tank		*initTank()
{
	struct s_tank	*tank;

	tank = (struct s_tank *)malloc(sizeof(struct s_tank));
	if (!tank)
		return (NULL);
	tank->stacks = (struct s_stack **)malloc(sizeof(struct s_stack *) * 100);
	if (!tank->stacks)
	{
		free(tank);
		return (NULL);
	}
	int				i = -1;
	while (++i < 100)
		tank->stacks[i] = 0;

	tank->n = 0;
	tank->stacks[tank->n] = stackInit();
	if (!tank->stacks[tank->n])
	{
		free(tank->stacks);
		free(tank);
		return (NULL);
	}
	tank->n++;
	return (tank);
}

struct s_stack	*stackInit(void)
{
	struct s_stack	*newstack;

	newstack = (struct s_stack *)malloc(sizeof(struct s_stack));
	if (!newstack)
		return (NULL);
	newstack->elem = NULL;
	newstack->sum = 0;
	return (newstack);
}

void				tankPush(struct s_tank *tank, int energy)
{
	if (!tank)
		return ;
	//Add a new stack to tank and add energy to that new stack
	if (tank->stacks[tank->n - 1]->sum + energy > 1000)
	{
		tank->stacks[tank->n] = stackInit();
		if (!tank->stacks[tank->n])
			return ;
		tank->stacks[tank->n]->sum += energy;
		push(tank->stacks[tank->n++], energy);
	}
	else
	{
		tank->stacks[tank->n - 1]->sum += energy;
		push(tank->stacks[tank->n - 1], energy);
	}
}

void			push(struct s_stack *stack, int energy)
{
	struct s_elem	*node;

	node = (struct s_elem *)malloc(sizeof(struct s_elem));
	if (!node)
		return ;
	node->energy = energy;
	node->next = stack->elem;
	stack->elem = node;
}

int					tankPop(struct s_tank *tank)
{
	int				popInt = 0;
	//Check if there is anything to pop, if not, remove the stack
	if (isEmpty(tank->stacks[tank->n - 1]))
	{
		tank->n--;
		free(tank->stacks[tank->n]);
	}
	popInt = pop(tank->stacks[tank->n - 1]);
	tank->stacks[tank->n - 1]->sum -= popInt;
	return (popInt);
}

int				pop(struct s_stack *stack)
{
	int				ret;
	struct s_elem	*tmp;

	if (isEmpty(stack))
		return (-1);
	tmp = stack->elem;
	ret = stack->elem->energy;
	stack->elem = stack->elem->next;
	free(tmp);
	return (ret);
}

int				isEmpty(struct s_stack *stack)
{
	return (stack->elem == NULL ? 1 : 0);
}

int				peek(struct s_stack *stack)
{
	return (isEmpty(stack) == 1 ? -1 : stack->elem->energy);
}