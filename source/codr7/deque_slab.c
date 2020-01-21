#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codr7/deque_pool.h"
#include "codr7/deque_slab.h"

struct c7_deque_slab *c7_deque_slab_new(struct c7_deque_pool *pool) {
  return c7_deque_slab_init(malloc(sizeof(struct c7_deque_slab) +
				   c7_align(0, pool->item_size) +
				   pool->slab_size * pool->item_size));
}

struct c7_deque_slab *c7_deque_slab_init(struct c7_deque_slab *slab) {
  slab->front = slab->back = 0;
  return slab;
}

void *c7_deque_slab_get(struct c7_deque_slab *slab, struct c7_deque_pool *pool, uint16_t i) {
  return c7_align(slab->items, pool->item_size) + i * pool->item_size;
}

uint16_t c7_deque_slab_count(const struct c7_deque_slab *slab) {
  return slab->back - slab->front;
}

void *c7_deque_slab_front(struct c7_deque_slab *slab, struct c7_deque_pool *pool) {
  return c7_deque_slab_get(slab, pool, slab->front);
}

void *c7_deque_slab_push_front(struct c7_deque_slab *slab, struct c7_deque_pool *pool) {
  return c7_deque_slab_get(slab,
			   pool,
			   slab->front ? --slab->front : slab->back++);
}

void c7_deque_slab_pop_front(struct c7_deque_slab *slab) {
  slab->front++;
}

void *c7_deque_slab_back(struct c7_deque_slab *slab, struct c7_deque_pool *pool) {
  return c7_deque_slab_get(slab, pool, slab->back - 1);
}

void *c7_deque_slab_push_back(struct c7_deque_slab *slab, struct c7_deque_pool *pool) {
  return c7_deque_slab_get(slab, pool, slab->back++);
}

void c7_deque_slab_pop_back(struct c7_deque_slab *slab) {
  slab->back--;
}
