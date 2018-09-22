#include "header.h"
#include <limits.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)
#define min3(a, b, c) ((a < b && a < c) ? a : (b < c ? b : c))
#define max3(a, b, c) ((a > b && a > c) ? a : (b > c ? b : c))

int getMin(struct s_node *root)
{
	int node;
	int l;
	int r;

	if (!root)
		return (INT_MAX);
	node = root->value;
	l = getMin(root->left);
	r = getMin(root->right);
  return (min3(l, node, r));
}

int getMax(struct s_node *root)
{
	int node;
	int l;
	int r;

	if (!root)
		return (INT_MIN);
	node = root->value;
	l = getMax(root->left);
	r = getMax(root->right);
  return (max3(l, node, r));
}

int isBST(struct s_node *root)
{
	if (!root)
		return (1);
	if ((root->left && getMax(root->left) > root->value) ||
      (root->right && getMin(root->right) <= root->value) ||
      (!isBST(root->left) || !isBST(root->right)))
		return (0);
	return (1);
}

int getSize(struct s_node *root)
{
	if (!root)
		return 0;
	return (1 + getSize(root->left) + getSize(root->right));
}

int getHeight(struct s_node *root)
{
	if (!root)
		return 0;
	return (max(getHeight(root->left), getHeight(root->right)) + 1);
}

int isBalanced(struct s_node *root)
{
  int lh, rh = 0;

  if (!root)
    return (1);

  lh = getHeight(root->left); 
  rh = getHeight(root->right);

  if(abs(lh-rh) <= 1 &&
    isBalanced(root->left) &&
    isBalanced(root->right)) 
    return (1);
  return (0);
}

struct s_info getInfo(struct s_node *root)
{
	struct s_info info;
	int height = 0;

	info.min = getMin(root);
	info.max = getMax(root);
	info.elements = getSize(root);
	info.height = getHeight(root);
	info.isBST = isBST(root);
	info.isBalanced = isBalanced(root);
	return info;
}