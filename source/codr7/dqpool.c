#include <stdlib.h>
#include "codr7/dqpool.h"
#include "codr7/dqslab.h"
#include "codr7/utils.h"

void c7_dqpool_init(struct c7_dqpool *pool,
		  uint16_t slab_size, uint16_t item_size) {
  pool->slab_size = slab_size;
  pool->item_size = item_size;
  c7_list_init(&pool->slabs);
}

void c7_dqpool_deinit(struct c7_dqpool *pool) {
  c7_list_do(&pool->slabs, b) {
    free(c7_baseof(b, struct c7_dqslab, list));
  }
}

struct c7_dqslab *c7_dqpool_get(struct c7_dqpool *pool) {
  return (pool->slabs.next == &pool->slabs)
    ? c7_dqslab_new(pool)
    : c7_dqslab_init(c7_baseof(c7_list_remove(pool->slabs.next),
			      struct c7_dqslab,
			      list));
}

void c7_dqpool_put(struct c7_dqpool *pool, struct c7_dqslab *slab) {
  c7_list_insert(&pool->slabs, &slab->list);
}
