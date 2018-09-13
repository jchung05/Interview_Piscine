#include "header.h"
#include <stdlib.h>
#include <string.h>

//Sum all ASCII values in string and modulo by length of string
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
	struct s_dict	*newDict = (struct s_dict)malloc(sizeof(struct s_dict));
	int				i = -1;

	if (!newDict)
		return (NULL);
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

struct s_item	*itemInit(char *key, struct s_art *value)
{
	struct s_item	*newItem = (struct s_item *)malloc(sizeof(struct s_item));

	if (!newItem)
		return NULL;
	newItem->key = key;
	newItem->value = value;
	newItem->next = NULL;
	return (newItem);
}

int				dictInsert(struct s_dict *dict, char *key, struct s_art *value)
{
	struct s_item		*newItem;
	struct s_item		*itr;
	size_t				idx;

	if (dict && key && value)
	{
		newItem = itemInit(key, value);
		if (!newItem)
			return (NULL);

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

struct s_art	*dictSearch(struct s_dict *dict, char *key)
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
	return (NULL);
}

int				searchPrice(struct s_dict *dict, char *name)
{
	struct s_art	*art;
	
	if (dict && name && (art = dictSearch(dict, name)))
		return (art->price);
	return (-1);
}