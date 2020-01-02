#ifndef C7_CHAN_H
#define C7_CHAN_H

#include <threads.h>
#include "codr7/deque.h"

struct c7_chan {
  struct c7_deque queue;
  mtx_t mutex;
  cnd_t put;
};

void c7_chan_init(struct c7_chan *chan, struct c7_dqpool *pool);
void c7_chan_deinit(struct c7_chan *chan);

#endif
