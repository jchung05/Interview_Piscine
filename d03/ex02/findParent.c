#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct s_node   *findParent(struct s_node *root, char *firstSpecies, char *secondSpecies)
{
  int       two;
  struct s_node *tmp;
  struct s_node *parent;

  two = 0;
  tmp = NULL;

  if (!strcmp(root->name, firstSpecies) || !strcmp(root->name, secondSpecies))
    return (root);

  for (int i = 0; root->children[i]; i += 1)
  {
    parent = findParent(root->children[i], firstSpecies, secondSpecies);
    if (parent == NULL)
      continue ;
    else if (parent && ++two)
      tmp = parent;
    else
      break ;
  }
  return (two == 2 ? root : tmp);
}