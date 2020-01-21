#ifndef C7_TREE_POOL_H
#define C7_TREE_POOL_H

#include <inttypes.h>
#include "codr7/list.h"

struct c7_tree_pool {
  uint16_t slab_size, value_size, node_size;
  struct c7_list slabs, nodes;
};

void c7_tree_pool_init(struct c7_tree_pool *pool,
		       uint16_t slab_size,
		       uint16_t value_size);

void c7_tree_pool_deinit(struct c7_tree_pool *pool);

struct c7_tree_node *c7_tree_pool_get(struct c7_tree_pool *pool);
void c7_tree_pool_put(struct c7_tree_pool *pool, struct c7_tree_node *node);
		   
#endif
