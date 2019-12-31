#ifndef C7_RBPOOL_H
#define C7_RBPOOL_H

#include <inttypes.h>
#include "codr7/list.h"

struct c7_rbpool {
  uint16_t slab_size, node_size;
  struct c7_list slabs, nodes;
};

void c7_rbpool_init(struct c7_rbpool *pool,
		    uint16_t slab_size,
		    uint16_t value_size);

void c7_rbpool_deinit(struct c7_rbpool *pool);

struct c7_rbnode *c7_rbpool_get(struct c7_rbpool *pool);
void c7_rbpool_put(struct c7_rbpool *pool, struct c7_rbnode *node);
		   
#endif
