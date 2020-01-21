#ifndef C7_TREE_SLAB_H
#define C7_TREE_SLAB_H

#include <inttypes.h>
#include "codr7/list.h"

struct c7_node;
struct c7_tree_pool;

struct c7_tree_slab {
  struct c7_list list;
  uint16_t free;
  uint8_t nodes[];
};

struct c7_tree_slab *c7_tree_slab_new(struct c7_tree_pool *pool);
void c7_tree_slab_free(struct c7_tree_slab *slab);

void *c7_tree_slab_get(struct c7_tree_slab *slab, struct c7_tree_pool *pool);

#endif
