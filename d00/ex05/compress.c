#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t			hash(char *input)
{
	long long	sum = 0;
	int			i = -1;

	while (input[++i])
		sum += input[i];
	return ((size_t)(sum % i));
}

struct s_dict	*dictInit(int capacity)
{
	struct s_dict	*newDict = (struct s_dict *)malloc(sizeof(struct s_dict));
	int				i = -1;

	if (!newDict)
		return (NULL);
	if (capacity < 1)
	{
		free(newDict);
		return (NULL);
	}
	newDict->capacity = capacity;
	newDict->items = (struct s_item **)malloc(sizeof(struct s_item *) * capacity);
	if (!newDict->items)
	{
		free(newDict);
		return (NULL);
	}
	else
		while (++i < capacity)
			newDict->items[i] = NULL;

	return (newDict);
}

struct s_item	*itemInit(char *key, int value)
{
	struct s_item	*newItem = (struct s_item *)malloc(sizeof(struct s_item));

	if (!newItem)
		return NULL;
	newItem->key = key;
	newItem->value = value;
	newItem->next = NULL;
	return (newItem);
}

int				dictInsert(struct s_dict *dict, char *key, int value)
{
	struct s_item		*newItem;
	struct s_item		*itr;
	size_t				idx;

	if (dict && key && value > 0 && value < 256)
	{
		newItem = itemInit(key, value);
		if (!newItem)
			return (-1);

		idx = hash(key);
		//Iterate to last LL item and append
		if (dict->items[idx])
		{
			itr = dict->items[idx];

			while (itr->next)
				itr = itr->next;
			itr->next = newItem;
		}
		else //Assign that array value with newItem
			dict->items[idx] = newItem;

		//Assumedly return the hash ID
		return (idx);
	}
	//Unsuccessful inserted
	return (-1);
}

int				dictSearch(struct s_dict *dict, char *key)
{
	struct s_item	*itr;
	size_t			idx;

	if (dict && key)
	{
		idx = hash(key);

		if (dict->items[idx])
		{
			itr = dict->items[idx];

			while (itr)
			{
				if (!strcmp(itr->key, key))
					return (itr->value);
				itr = itr->next;
			}
		}
	}
	//Error or not found
	return (-1);
}

char			*makeHeader(struct s_dict *dict, int *size)
{
	int len = 0;
	struct s_item		*tmp;

	//Pass once for total malloc size
	for (int i = 0; i < dict->capacity; i++)
	{
		tmp = dict->items[i];
		while (tmp) 
		{
			len += strlen(tmp->key) + 1;
			tmp = tmp->next;
		}
	}
	char *header = calloc(1, ++len + 1);
	*size = len;
	header[0] = '<';
	char *h = header + 1;

	//Pass again to copy everything into a return string
	for (int i = 0; i < dict->capacity; i++)
	{
		tmp = dict->items[i];
		while (tmp) 
		{
			int cur = strlen(tmp->key);
			strncpy(h, tmp->key, cur);
			h[cur] = ',';
			tmp = tmp->next;
			h = h + cur + 1;
		}
	}
	*(h - 1) = '>';
	return header;
};

char			*compress(char *book, struct s_dict *dict)
{
	int				headerSize = 0;
	char			*header = makeHeader(dict, &headerSize);

	char			*ret = (char *)malloc(headerSize + strlen(book) + 1);
	char			*tok = strtok(book, " ");
	int				ascii;
	int				itr = 0;
	char			asciinum[2];

	asciinum[1] = 0;

	strcat(&ret[itr], header);
	itr += headerSize;

	while (tok)
	{
		ascii = dictSearch(dict, tok);
		asciinum[0] = ascii;
		if (ascii != -1)//Add the ascii value into string instead of string
		{
			strcat(&ret[itr], "@");
			strcat(&ret[itr + 1], asciinum);
			itr += 2;
		}
		else
		{
			strcat(&ret[itr], tok);
			itr += strlen(tok);
		}
		strcat(&ret[itr], " ");
		itr += 1;

		tok = strtok(NULL, " ");
	}

	return (ret);
}