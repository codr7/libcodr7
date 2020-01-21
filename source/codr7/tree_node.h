#ifndef C7_TREE_NODE_H
#define C7_TREE_NODE_H

#include <inttypes.h>
#include <stdbool.h>
#include "codr7/compare.h"
#include "codr7/list.h"

struct c7_tree;

struct c7_tree_node {
  struct c7_list list;
  struct c7_tree_node *left, *right;
  bool red;
  uint8_t value[];
};

struct c7_tree_node *c7_tree_node_init(struct c7_tree_node *node);
void c7_tree_node_deinit(struct c7_tree_node *node, struct c7_tree *tree);

uint8_t *c7_tree_node_value(struct c7_tree_node *node, struct c7_tree *tree);
void c7_tree_node_push(struct c7_tree_node *node, struct c7_list *list);

void *c7_tree_node_find(struct c7_tree_node *node,
			struct c7_tree *tree,
			const void *key);

struct c7_tree_node *c7_tree_node_add(struct c7_tree_node *node,
				      struct c7_tree *tree,
				      const void *key,
				      void **value);

struct c7_tree_node *c7_tree_node_remove(struct c7_tree_node *node,
					 struct c7_tree *tree,
					 const void *key,
					 void **value);

#endif
