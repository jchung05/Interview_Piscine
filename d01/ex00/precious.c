#include "header.h"


t_node	*init(char c)
{
	t_node	*node;
	
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->c = c;
	node->next = NULL;
	node->prev = NULL;
	
	return (node);
}

t_node	*make_list(const char *s)
{
	static int		i;
	int				len;
	t_node				*head;
	t_node				*pitr;
	t_node				*itr;
	
	len = strlen(s);

	if (i < len)
	{
		head = init(s[i]);
		pitr = head;
		itr = head;
		i++;
	}
	
	while (i < len)
	{
		itr = init(s[i]);
		pitr->next = itr;
		itr->prev = pitr;
		pitr = itr;
		i++;
	}
	
	if (len > 0)
	{
		itr->next = head;
		head->prev = itr;
	}
	return (head);
}

char	*precious(int *text, int size)
{
	t_node		*list;
	static char	ret[512];
	int			i;
	int			j;
	
	if (!size)
		return (NULL);

	list = make_list(CS);
	
	i = 0;
	j = 0;

	while (i < size)
	{
		if (text[i] >= 0)
		{
			while (text[i] != 0)
			{
				list = list->next;
				text[i]--;
			}
		}
		else
		{
			while (text[i] != 0)
			{
				list = list->prev;
				text[i]++;
			}
		}
		ret[j++] = list->c;
		i++;
	}
	ret[j] = '\n';
	return (ret);
}
