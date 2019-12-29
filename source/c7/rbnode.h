#ifndef C7_RBNODE_H
#define C7_RBNODE_H

#include <inttypes.h>
#include <stdbool.h>
#include "c7/compare.h"
#include "c7/list.h"

struct c7_rbtree;

struct c7_rbnode {
  struct c7_list list;
  struct c7_rbnode *left, *right;
  bool red;
  uint8_t value[];
};

struct c7_rbnode *c7_rbnode_init(struct c7_rbnode *node);

void c7_rbnode_flip(struct c7_rbnode *node);
struct c7_rbnode *c7_rbnode_rotl(struct c7_rbnode *node);
struct c7_rbnode *c7_rbnode_rotr(struct c7_rbnode *node);

bool c7_rbnode_red(struct c7_rbnode *node);

void *c7_rbnode_find(struct c7_rbnode *node,
		     struct c7_rbtree *tree,
		     const void *key);

struct c7_rbnode *c7_rbnode_add(struct c7_rbnode *node,
				struct c7_rbtree *tree,
				const void *key,
				void **value);

bool c7_rbnode_while(struct c7_rbnode *node, c7_predicate_t fn, void *arg);

#endif
