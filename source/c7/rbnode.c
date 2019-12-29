#include <stddef.h>
#include "c7/rbnode.h"
#include "c7/rbpool.h"
#include "c7/rbtree.h"

struct c7_rbnode *c7_rbnode_init(struct c7_rbnode *node) {
  node->left = node->right = NULL;
  node->red = true;
  return node;
}

void c7_rbnode_flip(struct c7_rbnode *node) {
  node->red = !node->red;
  node->left->red = !node->left->red;
  node->right->red = !node->right->red;
}

struct c7_rbnode *c7_rbnode_rotl(struct c7_rbnode *node) {
  struct c7_rbnode *n = node->right;
  node->right = n->left;
  n->left = node;
  n->red = node->red;
  node->red = true;
  return n;
}
						   
struct c7_rbnode *c7_rbnode_rotr(struct c7_rbnode *node) {
  struct c7_rbnode *n = node->left;
  node->left = n->right;
  n->right = node;
  n->red = node->red;
  node->red = true;
  return n;
}

bool c7_rbnode_is_red(struct c7_rbnode *node) {
  return node && node->red;
}

void *c7_rbnode_find(struct c7_rbnode *node,
		     struct c7_rbtree *tree,
		     const void *key) {
  while (node) {
    switch (tree->compare(key, node->value)) {
    case C7_LT:
      node = node->left;
      break;
    case C7_GT:
      node = node->right;
      break;
    default:
      return node->value;
    }
  }

  return NULL;
}

struct c7_rbnode *c7_rbnode_add(struct c7_rbnode *node,
				struct c7_rbtree *tree,
				const void *key,
				void **value) {
  if (!node) {
    node = c7_rbpool_get(tree->pool);
    *value = node->value;
    return node;
  }
  
  if (c7_rbnode_is_red(node->left) && c7_rbnode_is_red(node->right)) {
    c7_rbnode_flip(node);
  }

  switch (tree->compare(key, node->value)) {
  case C7_LT:
    node->left = c7_rbnode_add(node->left, tree, key, value);
    break;
  case C7_GT:
    node->right = c7_rbnode_add(node->right, tree, key, value);
    break;
  default:
    *value = node->value;
  }

  if (c7_rbnode_is_red(node->right) && !c7_rbnode_is_red(node->left)) {
    node = c7_rbnode_rotl(node);
  }
  
  if (c7_rbnode_is_red(node->left) && c7_rbnode_is_red(node->left->left)) {
    node = c7_rbnode_rotr(node);
  }

  return node;
}

bool c7_rbnode_while(struct c7_rbnode *node, c7_predicate_t fn, void *arg) {
  return node
    ? c7_rbnode_while(node->left, fn, arg) &&
    fn(node->value, arg) &&
    c7_rbnode_while(node->right, fn, arg)
    : true;
}
