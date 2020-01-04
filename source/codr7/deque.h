#ifndef C7_DEQUE_H
#define C7_DEQUE_H

#include "codr7/dqslab.h"
#include "codr7/list.h"

#define _c7_deque_do(deque, i, _slab)					\
  c7_list_do(&(deque)->slabs, _slab)					\
  c7_dqslab_do(c7_baseof(_slab, struct c7_dqslab, list), (deque)->pool, i)

#define c7_deque_do(deque, i)			\
  _c7_deque_do(deque, i, c7_unique(slab))

struct c7_deque {
  struct c7_dqpool *pool;
  struct c7_list slabs;
  uint64_t count;
};

void c7_deque_init(struct c7_deque *deque, struct c7_dqpool *pool);
void c7_deque_clear(struct c7_deque *deque);
void *c7_deque_get(struct c7_deque *deque, uint64_t i);

void *c7_deque_front(struct c7_deque *deque);
void *c7_deque_push_front(struct c7_deque *deque);
void c7_deque_pop_front(struct c7_deque *deque);

void *c7_deque_back(struct c7_deque *deque);
void *c7_deque_push_back(struct c7_deque *deque);
void c7_deque_pop_back(struct c7_deque *deque);

#endif
