#include "codr7/chan.h"
#include "codr7/error.h"

void c7_chan_init(struct c7_chan *chan, struct c7_dqpool *pool) {
  c7_deque_init(&chan->queue, pool);
  int result = 0;

  if ((result = mtx_init(&chan->mutex, mtx_timed)) != thrd_success) {
    c7_error("Failed initializing chan mutex: %d", result);
  }

  if ((result = cnd_init(&chan->put)) != thrd_success) {
    c7_error("Failed initializing chan put: %d", result);
  }
}

void c7_chan_deinit(struct c7_chan *chan) {
  cnd_destroy(&chan->put);
  mtx_destroy(&chan->mutex);
  c7_deque_clear(&chan->queue);
}
