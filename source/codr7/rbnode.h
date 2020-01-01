#ifndef C7_RBNODE_H
#define C7_RBNODE_H

#include <inttypes.h>
#include <stdbool.h>
#include "codr7/compare.h"
#include "codr7/list.h"

struct c7_rbtree;

struct c7_rbnode {
  struct c7_list list;
  struct c7_rbnode *left, *right;
  bool red;
  uint8_t value[];
};

struct c7_rbnode *c7_rbnode_init(struct c7_rbnode *node);
void c7_rbnode_deinit(struct c7_rbnode *node, struct c7_rbtree *tree);

uint8_t *c7_rbnode_value(struct c7_rbnode *node);

void *c7_rbnode_find(struct c7_rbnode *node,
		     struct c7_rbtree *tree,
		     const void *key);

struct c7_rbnode *c7_rbnode_add(struct c7_rbnode *node,
				struct c7_rbtree *tree,
				const void *key,
				void **value);

struct c7_rbnode *c7_rbnode_remove(struct c7_rbnode *node,
				   struct c7_rbtree *tree,
				   const void *key,
				   void **value);

bool c7_rbnode_while(struct c7_rbnode *node, c7_predicate_t fn, void *arg);

#endif
