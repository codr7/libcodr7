#ifndef C7_TREE_H
#define C7_TREE_H

#include <stdint.h>

#include "codr7/compare.h"
#include "codr7/tree_node.h"

#define _c7_tree_do(tree, var, _stack, _node)				\
  struct c7_list _stack;						\
  c7_list_init(&_stack);						\
  if ((tree)->root) {							\
    c7_tree_node_push((tree)->root, &_stack);				\
  }									\
  struct c7_tree_node *_node = c7_baseof(c7_list_pop_front(&_stack),	\
					 struct c7_tree_node,		\
					 list);				\
  for (void *var =  _node ? c7_tree_node_value(_node, tree) : NULL;	\
       var;								\
       _node = c7_baseof(c7_list_pop_front(&_stack),			\
			 struct c7_tree_node,				\
			 list),						\
	 var = _node ? c7_tree_node_value(_node, tree) : NULL)

#define c7_tree_do(tree, var)					\
  _c7_tree_do(tree, var, c7_unique(stack), c7_unique(node))

struct c7_tree_node;
struct c7_tree_pool;

struct c7_tree {
  c7_compare_t compare;
  struct c7_tree_pool *pool;
  struct c7_tree_node *root;
  uint64_t count;
};

void c7_tree_init(struct c7_tree *tree,
		  c7_compare_t compare,
		  struct c7_tree_pool *pool);

void c7_tree_clear(struct c7_tree *tree);

void *c7_tree_find(struct c7_tree *tree, const void *key);
void *c7_tree_add(struct c7_tree *tree, const void *key);
void *c7_tree_remove(struct c7_tree *tree, const void *key);
  
#endif
