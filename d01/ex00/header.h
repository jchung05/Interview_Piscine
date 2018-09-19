#ifndef HEADER_H
# define HEADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*--------------------------------
  !! required
  --------------------------------*/
# define CS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 !?:;,.$&<>()+*-_="

typedef struct  s_node {
	char c;
	struct s_node *prev;
	struct s_node *next;
}               t_node;

/*--------------------------------
  :) function you must implement
  --------------------------------*/
char *precious(int *text, int size);

/*--------------------------------
  ?? test function used in main
  --------------------------------*/


/*--------------------------------
  &  your own other function
  --------------------------------*/

t_node  *make_list(const char *);
t_node  *init(char);

#endif
