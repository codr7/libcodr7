#ifndef C7_DEQUE_SLAB_H
#define C7_DEQUE_SLAB_H

#include <stdint.h>
#include "codr7/list.h"

#define _c7_deque_slab_do(slab, pool, i, _back)			\
  for (void *i = c7_align((slab)->items, (pool)->item_size) +	\
	 (slab)->front * (pool)->item_size,			\
	 *_back = (uint8_t *)i +				\
	 c7_deque_slab_count(slab) * (pool->item_size);		\
       i < _back;						\
       i = (uint8_t *)i + (pool)->item_size)

#define c7_deque_slab_do(slab, pool, i)			\
  _c7_deque_slab_do(slab, pool, i, c7_unique(back))

struct c7_deque_pool;

struct c7_deque_slab {
  struct c7_list list;
  uint16_t front, back;
  uint8_t items[]; 
};

struct c7_deque_slab *c7_deque_slab_new(struct c7_deque_pool *pool);
struct c7_deque_slab *c7_deque_slab_init(struct c7_deque_slab *slab);

void *c7_deque_slab_get(struct c7_deque_slab *slab, struct c7_deque_pool *pool, uint16_t i);
uint16_t c7_deque_slab_count(const struct c7_deque_slab *slab);

void *c7_deque_slab_front(struct c7_deque_slab *slab, struct c7_deque_pool *pool);
void *c7_deque_slab_push_front(struct c7_deque_slab *slab, struct c7_deque_pool *pool);
void c7_deque_slab_pop_front(struct c7_deque_slab *slab);

void *c7_deque_slab_back(struct c7_deque_slab *slab, struct c7_deque_pool *pool);
void *c7_deque_slab_push_back(struct c7_deque_slab *slab, struct c7_deque_pool *pool);
void c7_deque_slab_pop_back(struct c7_deque_slab *slab);

#endif
