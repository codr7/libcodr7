#include <stddef.h>
#include "codr7/rbnode.h"
#include "codr7/rbpool.h"
#include "codr7/rbtree.h"

struct c7_rbnode *c7_rbnode_init(struct c7_rbnode *node) {
  node->left = node->right = NULL;
  node->red = true;
  return node;
}

void c7_rbnode_deinit(struct c7_rbnode *node, struct c7_rbtree *tree) {
  struct c7_list queue;
  c7_list_init(&queue);
  c7_list_insert(&queue, &node->list);

  while (queue.next != &queue) {
    node = c7_baseof(queue.next, struct c7_rbnode, list);
    c7_list_remove(&node->list);
    
    if (node->left) {
      c7_list_insert(&queue, &node->left->list);
    }

    if (node->right) {
      c7_list_insert(&queue, &node->right->list);
    }
  
    c7_rbpool_put(tree->pool, node);
  }
}

uint8_t *c7_rbnode_value(struct c7_rbnode *node) {
  return c7_align(node->value, _Alignof(max_align_t));
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

bool c7_rbnode_red(struct c7_rbnode *node) {
  return node && node->red;
}

void *c7_rbnode_find(struct c7_rbnode *node,
		     struct c7_rbtree *tree,
		     const void *key) {
  while (node) {
    switch (tree->compare(key, c7_rbnode_value(node))) {
    case C7_LT:
      node = node->left;
      break;
    case C7_GT:
      node = node->right;
      break;
    default:
      return c7_rbnode_value(node);
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
    *value = c7_rbnode_value(node);
    tree->count++;
    return node;
  }
  
  if (c7_rbnode_red(node->left) && c7_rbnode_red(node->right)) {
    c7_rbnode_flip(node);
  }

  switch (tree->compare(key, c7_rbnode_value(node))) {
  case C7_LT:
    node->left = c7_rbnode_add(node->left, tree, key, value);
    break;
  case C7_GT:
    node->right = c7_rbnode_add(node->right, tree, key, value);
    break;
  default:
    return node;
  }

  if (c7_rbnode_red(node->right) && !c7_rbnode_red(node->left)) {
    node = c7_rbnode_rotl(node);
  }
  
  if (c7_rbnode_red(node->left) && c7_rbnode_red(node->left->left)) {
    node = c7_rbnode_rotr(node);
  }

  return node;
}

bool c7_rbnode_while(struct c7_rbnode *node, c7_predicate_t fn, void *arg) {
  return node
    ? c7_rbnode_while(node->left, fn, arg) &&
    fn(c7_rbnode_value(node), arg) &&
    c7_rbnode_while(node->right, fn, arg)
    : true;
}
