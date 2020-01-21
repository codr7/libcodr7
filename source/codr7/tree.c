#include <stddef.h>

#include "codr7/tree.h"

void c7_tree_init(struct c7_tree *tree, 
		  c7_compare_t compare,
		  struct c7_tree_pool *pool) {
  tree->compare = compare;
  tree->pool = pool;
  tree->root = NULL;
  tree->count = 0;
}

void c7_tree_clear(struct c7_tree *tree) {
  if (tree->root) {
    c7_tree_node_deinit(tree->root, tree);
    tree->root = NULL;
    tree->count = 0;
  }
}

void *c7_tree_find(struct c7_tree *tree, const void *key) {
  return c7_tree_node_find(tree->root, tree, key);
}

void *c7_tree_add(struct c7_tree *tree, const void *key) {
  void *v = NULL;
  tree->root = c7_tree_node_add(tree->root, tree, key, &v);
  tree->root->red = false;
  return v;
}

void *c7_tree_remove(struct c7_tree *tree, const void *key) {
  void *v = NULL;
  tree->root = c7_tree_node_remove(tree->root, tree, key, &v);
  tree->root->red = false;
  return v;
}
