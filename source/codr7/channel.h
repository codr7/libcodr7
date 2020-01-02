#ifndef C7_CHANNEL_H
#define C7_CHANNEL_H

#include <threads.h>
#include "codr7/deque.h"

struct c7_channel {
  struct c7_deque queue;
  mtx_t mutex;
  cnd_t cond;
};

void c7_channel_init(struct c7_channel *chan, struct c7_dqpool *pool);
void c7_channel_deinit(struct c7_channel *chan);

#endif
