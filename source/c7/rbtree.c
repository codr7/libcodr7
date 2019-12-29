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

struct c7_rbnode *c7_rbtree_find(struct c7_rbtree *tree, const void *key) {
  struct c7_rbnode *n = tree->root;
  
  while (n) {
    switch (tree->compare(key, n->value)) {
    case C7_LT:
      n = n->left;
      break;
    case C7_GT:
      n = n->right;
      break;
    default:
      return n;
    }
  }

  return NULL;
}

void *c7_rbtree_insert(struct c7_rbtree *tree, const void *key) {
  void *v = NULL;
  tree->root = c7_rbnode_insert(tree->root, tree, key, &v);
  tree->root->red = false;
  return v;
}
