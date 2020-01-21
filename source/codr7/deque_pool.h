#ifndef C7_DEQUE_POOL_H
#define C7_DEQUE_POOL_H

#include <stdint.h>
#include "codr7/list.h"

struct c7_deque_slab;

struct c7_deque_pool {
  uint16_t slab_size, item_size;
  struct c7_list slabs;
};

void c7_deque_pool_init(struct c7_deque_pool *pool,
			uint16_t slab_size, uint16_t item_size);

void c7_deque_pool_deinit(struct c7_deque_pool *pool);

struct c7_deque_slab *c7_deque_pool_get(struct c7_deque_pool *pool);
void c7_deque_pool_put(struct c7_deque_pool *pool, struct c7_deque_slab *slab);

#endif
