#include "header.h"

void  printReverse(struct s_node *lst)
{
  if (lst->next)
  {
    printReverse(lst->next);
    printf(" ");
  }
  if (lst)
    printf("%s", lst->word);
}