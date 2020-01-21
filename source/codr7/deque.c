#include "codr7/deque.h"
#include "codr7/deque_pool.h"
#include "codr7/deque_slab.h"
#include "codr7/utils.h"

void c7_deque_init(struct c7_deque *deque, struct c7_deque_pool *pool) {
  deque->pool = pool;
  c7_list_init(&deque->slabs);
  deque->count = 0;
}

void c7_deque_clear(struct c7_deque *deque) {
  c7_list_do(&deque->slabs, b) {
    c7_deque_pool_put(deque->pool, c7_baseof(b, struct c7_deque_slab, list));
  }

  c7_list_init(&deque->slabs);
  deque->count = 0;
}

void *c7_deque_get(struct c7_deque *deque, uint64_t i) {
  c7_list_do(&deque->slabs, bl) {
    struct c7_deque_slab *b = c7_baseof(bl, struct c7_deque_slab, list);
    uint16_t c = c7_deque_slab_count(b);
    
    if (c > i) {
      return c7_deque_slab_get(b, deque->pool, i);
    }

    i -= c;
  }

  return NULL;
}

void *c7_deque_front(struct c7_deque *deque) {
  return c7_deque_slab_front(c7_baseof(deque->slabs.next, struct c7_deque_slab, list),
			     deque->pool);
}

void *c7_deque_push_front(struct c7_deque *deque) {
  struct c7_list *b = deque->slabs.next;

  if (b == &deque->slabs || !c7_baseof(b, struct c7_deque_slab, list)->front) {
    c7_list_insert(deque->slabs.next, (b = &c7_deque_pool_get(deque->pool)->list));
  }

  deque->count++;
  return c7_deque_slab_push_front(c7_baseof(b, struct c7_deque_slab, list), deque->pool);
}

void c7_deque_pop_front(struct c7_deque *deque) {
  struct c7_deque_slab *b = c7_baseof(deque->slabs.next, struct c7_deque_slab, list);
  c7_deque_slab_pop_front(b);
  deque->count--;
  
  if (!c7_deque_slab_count(b)) {
    c7_list_remove(&b->list);
    c7_deque_pool_put(deque->pool, c7_baseof(b, struct c7_deque_slab, list));
  }
}

void *c7_deque_back(struct c7_deque *deque) {
  return c7_deque_slab_back(c7_baseof(deque->slabs.prev, struct c7_deque_slab, list),
			    deque->pool);
}

void *c7_deque_push_back(struct c7_deque *deque) {
  struct c7_list *b = deque->slabs.prev;

  if (b == &deque->slabs ||
      c7_baseof(b, struct c7_deque_slab, list)->back ==
      deque->pool->slab_size) {
    c7_list_insert(&deque->slabs, (b = &c7_deque_pool_get(deque->pool)->list));
  }

  deque->count++;
  return c7_deque_slab_push_back(c7_baseof(b, struct c7_deque_slab, list), deque->pool);
}

void c7_deque_pop_back(struct c7_deque *deque) {
  struct c7_deque_slab *b = c7_baseof(deque->slabs.prev, struct c7_deque_slab, list);
  c7_deque_slab_pop_back(b);
  deque->count--;
  
  if (!c7_deque_slab_count(b)) {
    c7_list_remove(&b->list);
    c7_deque_pool_put(deque->pool, c7_baseof(b, struct c7_deque_slab, list));
  }
}
