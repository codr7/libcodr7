#include <stddef.h>
#include "c7/rbnode.h"
#include "c7/rbtree.h"

void c7_rbtree_init(struct c7_rbtree *tree, 
		    c7_compare_t compare,
		    struct c7_rbpool *pool) {
  tree->compare = compare;
  tree->pool = pool;
  tree->root = NULL;
}

void c7_rbtree_deinit(struct c7_rbtree *tree) {
}

void *c7_rbtree_find(struct c7_rbtree *tree, const void *key) {
  return c7_rbnode_find(tree->root, tree, key);
}

void *c7_rbtree_add(struct c7_rbtree *tree, const void *key) {
  void *v = NULL;
  tree->root = c7_rbnode_add(tree->root, tree, key, &v);
  tree->root->red = false;
  return v;
}

bool c7_rbtree_while(struct c7_rbtree *tree, c7_predicate_t fn, void *arg) {
  return c7_rbnode_while(tree->root, fn, arg);
}
