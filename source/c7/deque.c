#include "c7/deque.h"
#include "c7/dqpool.h"
#include "c7/dqslab.h"
#include "c7/utils.h"

void c7_deque_init(struct c7_deque *deque, struct c7_dqpool *pool) {
  deque->pool = pool;
  c7_list_init(&deque->slabs);
  deque->count = 0;
}

void c7_deque_deinit(struct c7_deque *deque) {
  c7_list_do(&deque->slabs, b) {
    c7_dqpool_put(deque->pool, c7_baseof(b, struct c7_dqslab, list));
  }
}

void *c7_deque_get(struct c7_deque *deque, uint64_t i) {
  c7_list_do(&deque->slabs, bl) {
    struct c7_dqslab *b = c7_baseof(bl, struct c7_dqslab, list);
    uint16_t c = c7_dqslab_count(b);
    
    if (c > i) {
      return c7_dqslab_get(b, deque->pool, i);
    }

    i -= c;
  }

  return NULL;
}

void *c7_deque_front(struct c7_deque *deque) {
  return c7_dqslab_front(c7_baseof(deque->slabs.next, struct c7_dqslab, list),
			deque->pool);
}

void *c7_deque_push_front(struct c7_deque *deque) {
  struct c7_list *b = deque->slabs.next;

  if (b == &deque->slabs || !c7_baseof(b, struct c7_dqslab, list)->front) {
    c7_list_insert(deque->slabs.next, (b = &c7_dqpool_get(deque->pool)->list));
  }

  deque->count++;
  return c7_dqslab_push_front(c7_baseof(b, struct c7_dqslab, list), deque->pool);
}

void c7_deque_pop_front(struct c7_deque *deque) {
  struct c7_dqslab *b = c7_baseof(deque->slabs.next, struct c7_dqslab, list);
  c7_dqslab_pop_front(b);
  deque->count--;
  
  if (!c7_dqslab_count(b)) {
    c7_list_remove(&b->list);
    c7_dqpool_put(deque->pool, c7_baseof(b, struct c7_dqslab, list));
  }
}

void *c7_deque_back(struct c7_deque *deque) {
  return c7_dqslab_back(c7_baseof(deque->slabs.prev, struct c7_dqslab, list),
		       deque->pool);
}

void *c7_deque_push_back(struct c7_deque *deque) {
  struct c7_list *b = deque->slabs.prev;

  if (b == &deque->slabs ||
      c7_baseof(b, struct c7_dqslab, list)->back ==
      deque->pool->slab_size) {
    c7_list_insert(&deque->slabs, (b = &c7_dqpool_get(deque->pool)->list));
  }

  deque->count++;
  return c7_dqslab_push_back(c7_baseof(b, struct c7_dqslab, list), deque->pool);
}

void c7_deque_pop_back(struct c7_deque *deque) {
  struct c7_dqslab *b = c7_baseof(deque->slabs.prev, struct c7_dqslab, list);
  c7_dqslab_pop_back(b);
  deque->count--;
  
  if (!c7_dqslab_count(b)) {
    c7_list_remove(&b->list);
    c7_dqpool_put(deque->pool, c7_baseof(b, struct c7_dqslab, list));
  }
}
