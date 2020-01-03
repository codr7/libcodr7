#ifndef C7_CHAN_H
#define C7_CHAN_H

#include <threads.h>
#include "codr7/deque.h"

struct c7_chan {
  struct c7_deque queue;
  uint64_t queue_max;
  
  mtx_t mutex;
  cnd_t put, get;
};

void c7_chan_init(struct c7_chan *chan,
		  struct c7_dqpool *pool,
		  uint64_t queue_max);

void c7_chan_deinit(struct c7_chan *chan);

void *c7_chan_put_lock(struct c7_chan *chan, const struct timespec *deadline);
void c7_chan_put_unlock(struct c7_chan *chan);

void *c7_chan_get_lock(struct c7_chan *chan, const struct timespec *deadline);
void c7_chan_get_unlock(struct c7_chan *chan);

#endif
