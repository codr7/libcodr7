#include <stdlib.h>

#include "codr7/tree_node.h"
#include "codr7/tree_pool.h"
#include "codr7/tree_slab.h"

struct c7_tree_slab *c7_tree_slab_new(struct c7_tree_pool *pool) {
  struct c7_tree_slab *slab = malloc(sizeof(struct c7_tree_slab) +
				     pool->slab_size * pool->node_size);
  c7_list_insert(&pool->slabs, &slab->list);
  slab->free = pool->slab_size;
  return slab;
}

void c7_tree_slab_free(struct c7_tree_slab *slab) {
  free(slab);
}

void *c7_tree_slab_get(struct c7_tree_slab *slab, struct c7_tree_pool *pool) {
  uint8_t *p = slab->nodes + (pool->slab_size - slab->free--) * pool->node_size;
  return c7_align(p, _Alignof(struct c7_tree_node));
}
