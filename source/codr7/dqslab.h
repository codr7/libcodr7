#ifndef C7_DQSLAB_H
#define C7_DQSLAB_H

#include <stdint.h>
#include "codr7/list.h"

#define _c7_dqslab_do(b, p, i, _back)				\
  for (void *i = (b)->items + (b)->front * (p)->item_size,	\
	 *_back = (b)->items + (b)->back * (p)->item_size;	\
       i < _back;						\
       i = (uint8_t *)i + (p)->item_size)

#define c7_dqslab_do(b, p, i)			\
  _c7_dqslab_do(b, p, i, c7_unique(back))

struct c7_dqpool;

struct c7_dqslab {
  struct c7_list list;
  uint16_t front, back;
  uint8_t items[]; 
};

struct c7_dqslab *c7_dqslab_new(struct c7_dqpool *pool);
struct c7_dqslab *c7_dqslab_init(struct c7_dqslab *slab);

void *c7_dqslab_get(struct c7_dqslab *slab, struct c7_dqpool *pool, uint16_t i);
uint16_t c7_dqslab_count(const struct c7_dqslab *slab);

void *c7_dqslab_front(struct c7_dqslab *slab, struct c7_dqpool *pool);
void *c7_dqslab_push_front(struct c7_dqslab *slab, struct c7_dqpool *pool);
void c7_dqslab_pop_front(struct c7_dqslab *slab);

void *c7_dqslab_back(struct c7_dqslab *slab, struct c7_dqpool *pool);
void *c7_dqslab_push_back(struct c7_dqslab *slab, struct c7_dqpool *pool);
void c7_dqslab_pop_back(struct c7_dqslab *slab);

#endif
