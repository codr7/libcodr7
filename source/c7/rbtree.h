#ifndef C7_RBTREE_H
#define C7_RBTREE_H

#include "c7/compare.h"

struct c7_rbnode;
struct c7_rbpool;

struct c7_rbtree {
  c7_compare_t compare;
  struct c7_rbpool *pool;
  struct c7_rbnode *root;
};

void c7_rbtree_init(struct c7_rbtree *tree,
		    c7_compare_t compare,
		    struct c7_rbpool *pool);

void c7_rbtree_deinit(struct c7_rbtree *tree);

void *c7_rbtree_find(struct c7_rbtree *tree, const void *key);
void *c7_rbtree_add(struct c7_rbtree *tree, const void *key);
  
#endif
