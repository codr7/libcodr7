#ifndef C7_RBTREE_H
#define C7_RBTREE_H

#include <stdint.h>

#include "codr7/compare.h"
#include "codr7/rbnode.h"

#define _c7_rbtree_do(tree, var, _stack, _node)				\
  struct c7_list _stack;						\
  c7_list_init(&_stack);						\
  if ((tree)->root) {							\
    c7_rbnode_push((tree)->root, &_stack);				\
  }									\
  struct c7_rbnode *_node = c7_baseof(c7_list_pop_front(&_stack),	\
				      struct c7_rbnode,			\
				      list);				\
  for (void *var =  _node ? c7_rbnode_value(_node, tree) : NULL;	\
       var;								\
       _node = c7_baseof(c7_list_pop_front(&_stack),			\
			 struct c7_rbnode,				\
			 list),						\
	 var = _node ? c7_rbnode_value(_node, tree) : NULL)

#define c7_rbtree_do(tree, var)					\
  _c7_rbtree_do(tree, var, c7_unique(stack), c7_unique(node))

struct c7_rbnode;
struct c7_rbpool;

struct c7_rbtree {
  c7_compare_t compare;
  struct c7_rbpool *pool;
  struct c7_rbnode *root;
  uint64_t count;
};

void c7_rbtree_init(struct c7_rbtree *tree,
		    c7_compare_t compare,
		    struct c7_rbpool *pool);

void c7_rbtree_clear(struct c7_rbtree *tree);

void *c7_rbtree_find(struct c7_rbtree *tree, const void *key);
void *c7_rbtree_add(struct c7_rbtree *tree, const void *key);
void *c7_rbtree_remove(struct c7_rbtree *tree, const void *key);
  
#endif
