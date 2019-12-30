#include <stdlib.h>
#include "codr7/rbslab.h"
#include "codr7/rbpool.h"

struct c7_rbslab *c7_rbslab_new(struct c7_rbpool *pool) {
  struct c7_rbslab *slab = malloc(sizeof(struct c7_rbslab) +
			      pool->slab_size * pool->node_size);
  c7_list_insert(&pool->slabs, &slab->list);
  slab->free = pool->slab_size;
  return slab;
}

void c7_rbslab_free(struct c7_rbslab *slab) {
  free(slab);
}

void *c7_rbslab_get(struct c7_rbslab *slab, struct c7_rbpool *pool) {
  return slab->nodes + (pool->slab_size - slab->free--) * pool->node_size;
}
