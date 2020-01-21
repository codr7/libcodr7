#include <stdlib.h>

#include "codr7/deque_pool.h"
#include "codr7/deque_slab.h"
#include "codr7/utils.h"

void c7_deque_pool_init(struct c7_deque_pool *pool,
			uint16_t slab_size, uint16_t item_size) {
  pool->slab_size = slab_size;
  pool->item_size = item_size;
  c7_list_init(&pool->slabs);
}

void c7_deque_pool_deinit(struct c7_deque_pool *pool) {
  c7_list_do(&pool->slabs, b) {
    free(c7_baseof(b, struct c7_deque_slab, list));
  }
}

struct c7_deque_slab *c7_deque_pool_get(struct c7_deque_pool *pool) {
  return (pool->slabs.next == &pool->slabs)
    ? c7_deque_slab_new(pool)
    : c7_deque_slab_init(c7_baseof(c7_list_remove(pool->slabs.next),
				   struct c7_deque_slab,
				   list));
}

void c7_deque_pool_put(struct c7_deque_pool *pool, struct c7_deque_slab *slab) {
  c7_list_insert(&pool->slabs, &slab->list);
}
