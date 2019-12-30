#ifndef C7_DQPOOL_H
#define C7_DQPOOL_H

#include <stdint.h>
#include "codr7/list.h"

struct c7_dqslab;

struct c7_dqpool {
  uint16_t slab_size, item_size;
  struct c7_list slabs;
};

void c7_dqpool_init(struct c7_dqpool *pool,
		    uint16_t slab_size, uint16_t item_size);

void c7_dqpool_deinit(struct c7_dqpool *pool);

struct c7_dqslab *c7_dqpool_get(struct c7_dqpool *pool);
void c7_dqpool_put(struct c7_dqpool *pool, struct c7_dqslab *slab);

#endif
