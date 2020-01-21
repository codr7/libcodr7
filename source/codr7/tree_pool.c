#include "codr7/tree_node.h"
#include "codr7/tree_pool.h"
#include "codr7/tree_slab.h"

void c7_tree_pool_init(struct c7_tree_pool *pool,
		       uint16_t slab_size, uint16_t value_size) {
  pool->slab_size = slab_size;
  pool->value_size = value_size;

  pool->node_size = 
    sizeof(struct c7_tree_node) + _Alignof(struct c7_tree_node) +
    value_size + c7_align(0, value_size);
      
  c7_list_init(&pool->slabs);
  c7_list_init(&pool->nodes);
  c7_tree_slab_new(pool);
}

void c7_tree_pool_deinit(struct c7_tree_pool *pool) {
  c7_list_do(&pool->slabs, b) {
    c7_tree_slab_free(c7_baseof(b, struct c7_tree_slab, list));
  }
}

struct c7_tree_node *c7_tree_pool_get(struct c7_tree_pool *pool) {
  struct c7_list *nl = pool->nodes.next;
  struct c7_tree_node *n = NULL;
  
  if (nl == &pool->nodes) {
    struct c7_tree_slab *slab = c7_baseof(pool->slabs.prev, struct c7_tree_slab, list);

    if (!slab->free) {
      slab = c7_tree_slab_new(pool);
    }
    
    n = c7_tree_slab_get(slab, pool);
  } else {
    c7_list_remove(nl);
    n = c7_baseof(nl, struct c7_tree_node, list);
  }
  
  return c7_tree_node_init(n);
}

void c7_tree_pool_put(struct c7_tree_pool *pool, struct c7_tree_node *node) {
  c7_list_insert(&pool->nodes, &node->list);
}
