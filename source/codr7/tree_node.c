#include <stddef.h>

#include "codr7/tree.h"
#include "codr7/tree_node.h"
#include "codr7/tree_pool.h"

struct c7_tree_node *c7_tree_node_init(struct c7_tree_node *node) {
  node->left = node->right = NULL;
  node->red = true;
  return node;
}

void c7_tree_node_deinit(struct c7_tree_node *node, struct c7_tree *tree) {
  struct c7_list queue;
  c7_list_init(&queue);
  c7_list_insert(&queue, &node->list);

  while (queue.next != &queue) {
    node = c7_baseof(queue.next, struct c7_tree_node, list);
    c7_list_remove(&node->list);
    
    if (node->left) {
      c7_list_insert(&queue, &node->left->list);
    }

    if (node->right) {
      c7_list_insert(&queue, &node->right->list);
    }
  
    c7_tree_pool_put(tree->pool, node);
  }
}

uint8_t *c7_tree_node_value(struct c7_tree_node *node, struct c7_tree *tree) {
  return c7_align(node->value, tree->pool->value_size);
}

void c7_tree_node_push(struct c7_tree_node *node, struct c7_list *list) {
  if (node->left) {
    c7_tree_node_push(node->left, list);
  }
  
  c7_list_push_back(list, &node->list);

  if (node->right) {
    c7_tree_node_push(node->right, list);
  }
}

void *c7_tree_node_find(struct c7_tree_node *node,
			struct c7_tree *tree,
			const void *key) {
  while (node) {
    switch (tree->compare(key, c7_tree_node_value(node, tree))) {
    case C7_LT:
      node = node->left;
      break;
    case C7_GT:
      node = node->right;
      break;
    default:
      return c7_tree_node_value(node, tree);
    }
  }

  return NULL;
}

static bool red(struct c7_tree_node *node) {
  return node && node->red;
}

static void flip(struct c7_tree_node *node) {
  node->red = !node->red;
  node->left->red = !node->left->red;
  node->right->red = !node->right->red;
}

static struct c7_tree_node *rotl(struct c7_tree_node *node) {
  struct c7_tree_node *n = node->right;
  node->right = n->left;
  n->left = node;
  n->red = node->red;
  node->red = true;
  return n;
}

static struct c7_tree_node *rotr(struct c7_tree_node *node) {
  struct c7_tree_node *n = node->left;
  node->left = n->right;
  n->right = node;
  n->red = node->red;
  node->red = true;
  return n;
}

static struct c7_tree_node *fix(struct c7_tree_node *node) {
  if (red(node->right)) {
    node = rotl(node);
  }
  
  if (red(node->left) && red(node->left->left)) {
    node = rotr(node);
  }

  if (red(node->left) && red(node->right)) {
    flip(node);
  }

  return node;
}

struct c7_tree_node *c7_tree_node_add(struct c7_tree_node *node,
				      struct c7_tree *tree,
				      const void *key,
				      void **value) {
  if (!node) {
    node = c7_tree_pool_get(tree->pool);
    *value = c7_tree_node_value(node, tree);
    tree->count++;
    return node;
  }
  
  switch (tree->compare(key, c7_tree_node_value(node, tree))) {
  case C7_LT:
    node->left = c7_tree_node_add(node->left, tree, key, value);
    break;
  case C7_GT:
    node->right = c7_tree_node_add(node->right, tree, key, value);
    break;
  default:
    return node;
  }

  return fix(node);
}

static struct c7_tree_node *move_red_left(struct c7_tree_node *node) {
  flip(node);

  if (red(node->right->left)) {
    node->right = rotr(node->right);
    node = rotl(node);
    flip(node);
  }

  return node;
}

static struct c7_tree_node *remove_min(struct c7_tree_node *in,
				       struct c7_tree_node **out) {
  if (!in->left) {
    *out = in;
    return NULL;
  }

  if (!red(in->left) && !red(in->left->left)) {
    in = move_red_left(in);
  }

  in->left = remove_min(in->left, out);
  return fix(in);
}

struct c7_tree_node *c7_tree_node_remove(struct c7_tree_node *node,
					 struct c7_tree *tree,
					 const void *key,
					 void **value) {
  if (tree->compare(key, c7_tree_node_value(node, tree)) == C7_LT) {
    if (!red(node->left) && !red(node->left->left)) {
      node = move_red_left(node);
    }

    node->left = c7_tree_node_remove(node->left, tree, key, value);
  } else {
    if (red(node->left)) {
      node = rotr(node);
    }

    void *v = NULL;
    
    if (tree->compare(key, (v = c7_tree_node_value(node, tree))) == C7_EQ &&
	!node->right) {
      *value = v;
      c7_tree_pool_put(tree->pool, node);
      tree->count--;
      return NULL;
    }

    if (!red(node->right) && !red(node->right->left)) {
      flip(node);

      if (red(node->left->left)) {
	node = rotr(node);
	flip(node);
      }
    }

    if (tree->compare(key, (v = c7_tree_node_value(node, tree))) == C7_EQ) {
      *value = v;
      c7_tree_pool_put(tree->pool, node);
      struct c7_tree_node *l = node->left, *r = remove_min(node->right, &node);
      node->left = l;
      node->right = r;
      tree->count--;
    } else {
      node->right = c7_tree_node_remove(node->right, tree, key, value);
    }
  }

  return fix(node);
}
