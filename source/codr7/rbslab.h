#ifndef C7_RBSLAB_H
#define C7_RBSLAB_H

#include <inttypes.h>
#include "codr7/list.h"

struct c7_node;
struct c7_rbpool;

struct c7_rbslab {
  struct c7_list list;
  uint16_t free;
  uint8_t nodes[];
};

struct c7_rbslab *c7_rbslab_new(struct c7_rbpool *pool);
void c7_rbslab_free(struct c7_rbslab *slab);

void *c7_rbslab_get(struct c7_rbslab *slab, struct c7_rbpool *pool);

#endif
