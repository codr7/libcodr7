#include "codr7/rbnode.h"
#include "codr7/rbpool.h"
#include "codr7/rbslab.h"

void c7_rbpool_init(struct c7_rbpool *pool,
		    uint16_t slab_size, uint16_t value_size) {
  pool->slab_size = slab_size;
  pool->node_size = sizeof(struct c7_rbnode) + value_size;
  c7_list_init(&pool->slabs);
  c7_list_init(&pool->nodes);
  c7_rbslab_new(pool);
}

void c7_rbpool_deinit(struct c7_rbpool *pool) {
  c7_list_do(&pool->slabs, b) {
    c7_rbslab_free(c7_baseof(b, struct c7_rbslab, list));
  }
}

struct c7_rbnode *c7_rbpool_get(struct c7_rbpool *pool) {
  struct c7_list *nl = pool->nodes.next;
  struct c7_rbnode *n = NULL;
  
  if (nl == &pool->nodes) {
    struct c7_rbslab *slab = c7_baseof(pool->slabs.prev, struct c7_rbslab, list);

    if (!slab->free) {
      slab = c7_rbslab_new(pool);
    }
    
    n = c7_rbslab_get(slab, pool);
  } else {
    c7_list_remove(nl);
    n = c7_baseof(nl, struct c7_rbnode, list);
  }
  
  return c7_rbnode_init(n);
}
